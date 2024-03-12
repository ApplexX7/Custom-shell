


#include "../parsing/minishell.h"

int set_fd(int *set, t_tree *root)
{
  int fd;

  if (root->output_file)
  {
    //printf("%s\n", root->output_file);
    fd = open(root->output_file, O_WRONLY | O_CREAT, 0644);
    if (fd == -1)
      return (perror("open"), 1);
    //manage_fds(fd, CAPTURE)   
    return (*set = fd, 0);
  }
  else
    return (*set = root->out_fd, 0);
}

int ft_echo(t_tree *root)
{
  int nflag;
  int fd;
  t_list *lst;

  lst = root->node;
  if (set_fd(&fd, root))
    return (1);
  lst = lst->next;
  nflag = 0;
  if (!ft_strncmp(lst->content, "-n", 3))
  {
    nflag = 1;
    lst = lst->next;
  }
  while (lst)
  {
    ft_putstr_fd(lst->content, fd);
    ft_putstr_fd(" ", fd);
    lst = lst->next;
  }
  if (!nflag)
    ft_putstr_fd("\n", fd);
  if (fd != 1)
    close(fd);
  return (0);
}

int is_valid_arg_name(char *start, char *end)
{
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
  else if (&content[ft_strlen(content) - 1] == eq)
    return (ft_putstr_fd("export: not a valid identifier\n", 2), 0);
  else if (!is_valid_arg_name(content, eq))
    return (ft_putstr_fd("export: not a valid identifier\n", 2), 0);
  return (1);
}

void print_export(t_list *lst, int fd)
{
  bubbleSort(lst);
  while (lst)
  {
    ft_putstr_fd("declare -x ", fd);
    ft_putstr_fd(lst->content, fd);
    ft_putstr_fd("\n", fd);
    lst = lst->next;
  }
}

// allocs: key, value
int get_key_value(char *content, char **key, char **value, int *join)
{
  char *eq;
  char *key_;
  char *value_;

  eq = ft_strchr(content, '=');
  if (key)
    key_ = ft_substr(content, 0, eq - content);
  if (value)
    value_ = ft_substr(eq, 1, ft_strlen(content) - ft_strlen(eq));
  if (key_ && key)
  {
    if (key_[ft_strlen(key_) - 1] == '+')
    {
      if (join)
        *join = 1;
      key_[ft_strlen(key_) - 1] = '\0';
    }
  }
  *key = key_;
  *value = value_;
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
      if (!new)
        return (perror("concat_and_add: malloc"), 1);
      free(tmp->content);
      tmp->content = new;
      return (0);
    }
    tmp = tmp->next;
  }
  key = ft_strjoin(key, "=");
  if (!key)
    return (perror("concat_and_add: malloc"), 1);
  new = ft_strjoin(key, value);
  if (!new)
    return (perror("concat_and_add: malloc"), 1);
  if (new_and_add(local_env, new, '\''))
    return (perror("concat_and_add: malloc"), 1);
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
    if (new_and_add(local_env, lst->content, lst->is_op))
      return (ft_putstr_fd("export: error adding new entry\n", 2), 1);
  }
  return (0);
}

// allocs: local_env
int ft_export(t_tree *root)
{
  static t_list *local_env = NULL;
  t_list *tmp;
  int fd;

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
    (print_export(local_env, fd), close(fd));
  }
  return (0);
}

int main(void)
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
  t_tree t = {node, NULL, NULL, 0, 1, NULL, NULL};
  ft_export(&t);
  //ft_lstclear(&node, &free);
  node = NULL;
  ft_lstadd_back(&node, ft_lstnew("export"));
  t.node = node;
  ft_export(&t);
}

/*
int main(void)
{
  t_list *node;

  node = NULL;
  ft_lstadd_back(&node, ft_lstnew("echo"));
  //ft_lstadd_back(&node, ft_lstnew("-n"));
  ft_lstadd_back(&node, ft_lstnew("hello"));
  ft_lstadd_back(&node, ft_lstnew("world"));
  ft_lstadd_back(&node, ft_lstnew("hello"));
  t_tree t = {node, NULL, NULL, 0, 1, NULL, "test"};
  ft_echo (&t);
}
*/
