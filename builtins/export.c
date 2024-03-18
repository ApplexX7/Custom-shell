
#include "../parsing/minishell.h"

int init_envs(t_list **local_env, char **env)
{
  get_exported_arg_value(NULL, local_env, 0);
  ft_env(NULL, local_env);
  if (init_local_env(local_env, env))
    return (perror("init_local_env: malloc"), 1);
  return (0);
}

// allocs: local_env
int ft_export(t_tree *root, char **env, int init)
{
  static t_list *local_env = NULL;
  t_list *tmp;
  int fd;

  if (init)
    return (init_envs(&local_env, env));
  tmp = root->node;
  tmp = tmp->next;
  if (tmp)
  {
    while (tmp)
    {
      if (check_export_syntax(tmp->content))
      {
        if (add_export_node(tmp, &local_env))
          return (1);
      }
      tmp = tmp->next;
    }
  }
  else
  {
    if (set_fd(&fd, root))
      return (ft_putstr_fd("export: error opening file\n", fd), 1);
    if (print_export(local_env, fd))
      return (1);
  }
  return (0);
}

char *get_exported_arg_value(char *arg, t_list **local_lst, int free_bit)
{
  static t_list **lst = NULL;
  t_list *tmp;

  if (free_bit)
    (ft_lstclear(lst, &free), *lst = NULL);
  else if (local_lst)
    lst = local_lst;
  else if (lst)
  {
    tmp = *lst;
    while (tmp)
    {
      if (!ft_strncmp(arg, tmp->content, ft_strlen(arg)))
        return ((char *) tmp->content + ft_strlen(arg) + 1);
      tmp = tmp->next;
    }
  }
  return (NULL);
}

int init_local_env(t_list **local_env, char **env)
{
  t_list *new;
  int i;

  new = NULL;
  i = 0;
  while (env[i])
  {
    if (new_and_add(&new, env[i], '\''))
      return (ft_lstclear(&new, &free), 1);
    i++;
  }
  *local_env = new;
  return (0);
}

// allocs: key, value
int add_export_node(t_list *lst, t_list **local_env)
{
  char *key;
  char *value;
  int join;

  join = 0;
  get_key_value(lst->content, &key, &value, &join);
  if (join)
  {
    if (concat_and_add(key, value, local_env))
      return (1);
  }
  else
  {
    if (search_and_add(local_env, key, value))
      return (free(key), free(value), ft_putstr_fd("export: error adding new entry\n", 2), 1);
  }
  return (0);
}

int search_and_add(t_list **local_env, char *key, char *value)
{
  t_list *lst;

  lst = *local_env;
  while (lst)
  {
    if (!ft_strncmp(lst->content, key, min(ft_strlen(key), ft_strlen(lst->content))))
    {
      free(lst->content);
      key = ft_strjoin(key, "=");
      if (!key)
        return (perror("search_and_add"), 1);
      value = ft_strjoin(key, value);
      if (!value)
        return (perror("search_and_add"), 1);
      lst->content = ft_strdup(value);
      if (lst->content == NULL)
        return (perror("search_and_add"), 1);
      return (0);
    }
    lst = lst->next;
  }
  if (export_add_key_value(local_env, key, value))
    return (ft_putstr_fd("export: error adding new entry\n", 2), 1);
  return (0);
}

int is_valid_arg_name(char *start, char *end)
{
  if (ft_isdigit(*start))
    return (0);
  while (start < end)
  {
    if (!ft_isalpha(*start) && !ft_isdigit(*start) && *start != '_')
      return (0);
    start++;
  }
  return (1);
}

int check_export_syntax(char *content)
{
  char *eq;

  eq = ft_strchr(content, '=');
  if (eq == NULL)
    return (1);
  else if (eq != content && *(eq - 1) == '+')
    eq--;
  else if (content == eq)
    return (ft_putstr_fd("export: not a valid identifier\n", 2), 0);
  //else if (&content[ft_strlen(content) - 1] == eq)
    //return (ft_putstr_fd("export: not a valid identifier\n", 2), 0);
  else if (!is_valid_arg_name(content, eq))
    return (ft_putstr_fd("export: not a valid identifier\n", 2), 0);
  return (1);
}

// closes fd at end
int print_export(t_list *lst, int fd)
{
  char *eq;

  bubbleSort(lst);
  while (lst)
  {
    ft_putstr_fd("declare -x ", fd);
    eq = ft_strchr(lst->content, '=');
    if (!eq)
    {
      ft_putstr_fd(lst->content, fd);
      ft_putstr_fd("\n", fd);
    }
    else
    {
      ft_putnstr_fd(lst->content, fd, eq - (char *) lst->content + 1);
      ft_putstr_fd("\"", fd);
      ft_putstr_fd(eq + 1, fd);
      ft_putstr_fd("\"\n", fd);
    }
    lst = lst->next;
  }
  if (fd != 1 && ft_close(fd) == -1)
      return (perror("close"), 1);
  return (0);
}

// allocs: key, value
int get_key_value(char *content, char **key, char **value, int *join)
{
  char *eq;
  char *k;
  char *v;

  eq = ft_strchr(content, '=');
  if (key)
    k = ft_substr(content, 0, eq - content);
  if (value && eq)
    v = ft_substr(eq, 1, ft_strlen(eq) - 1);
  if (key && k)
  {
    if (k[ft_strlen(k) - 1] == '+')
    {
      if (join)
        *join = 1;
      k[ft_strlen(k) - 1] = '\0';
    }
  }
  if (key)
    *key = k;
  if (!eq)
    *value = NULL;
  else if (value)
    *value = v;
  return (0);
}

// allocs: new
int concat_and_add(char *key, char *value, t_list **local_env)
{
  char *new;
  t_list *tmp;

  tmp = *local_env;
  while (tmp)
  {
    if (!ft_strncmp(tmp->content, key, min(ft_strlen(tmp->content), ft_strlen(key))))
    {
      new = ft_strjoin(tmp->content, value);
      (free(key), free(value));
      if (!new)
        return (perror("concat_and_add: malloc"), 1);
      free(tmp->content);
      tmp->content = new;
      return (0);
    }
    tmp = tmp->next;
  }
  if (export_add_key_value(local_env, key, value))
    return (perror("concat_and_add: malloc"), 1);
  return (0);
}

// allocs: new
// frees key and value
int export_add_key_value(t_list **dest, char *key, char *value)
{
  char *new;
  char *tmp;

  tmp = key;
  if (value)
  {
    tmp = ft_strjoin(key, "=");
    free(key);
  }
  if (!tmp)
    return (perror("export_add_key_value"), 1);
  new = tmp;
  if (value)
  {
    new = ft_strjoin(tmp, value);
    free(value);
    if (!new)
      return (perror("export_add_key_value"), 1);
  }
  if (new_and_add(dest, new, '\''))
    return (free(new), ft_putstr_fd("export: error adding new entry\n", 2), 1);
  free(new);
  return (0);
}

/*
int main(int argc, char **argv, char **env)
{
  t_list *node;
  node = NULL;
  ft_lstadd_back(&node, ft_lstnew("export"));
  ft_lstadd_back(&node, ft_lstnew("hello=ssss"));
  ft_lstadd_back(&node, ft_lstnew("world="));
  ft_lstadd_back(&node, ft_lstnew("=hello"));
  ft_lstadd_back(&node, ft_lstnew("=hello"));
  ft_lstadd_back(&node, ft_lstnew("a=hello"));
  ft_lstadd_back(&node, ft_lstnew("aaaa=hello"));
  ft_lstadd_back(&node, ft_lstnew("aa-aa=hello"));
  ft_lstadd_back(&node, ft_lstnew("aaaa+=hello"));
  ft_lstadd_back(&node, ft_lstnew("aaaa+=hello"));
  ft_lstadd_back(&node, ft_lstnew("aaaa+=hello"));
  ft_lstadd_back(&node, ft_lstnew("testest+=hello"));
  ft_lstadd_back(&node, ft_lstnew("aaaa=hello"));
  ft_lstadd_back(&node, ft_lstnew("arg"));
  t_tree t = {node, NULL, NULL, 0, 1, NULL, NULL};
  ft_export(&t, env);
  //ft_lstclear(&node, &free);
  node = NULL;
  ft_lstadd_back(&node, ft_lstnew("export"));
  t.node = node;
  ft_export(&t, env);
  printf("====================\n");
  ft_env(&t, NULL);
}
*/
