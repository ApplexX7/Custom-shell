

#include "minishell.h"

// allocs: arg
char *get_masked_portion(char *str, char *mask)
{
  char *start;
  char *end;
  char *arg;


  start = ft_strchr(mask, '1');
  end = ft_strchr(start, '0');
  start = &str[start - mask];
  end = &str[end - mask];
  arg = ft_substr(start, 0, end - start);
  if (!arg)
    return (perror("malloc"), NULL);
  return (arg);
}

char *get_env_value(char *arg)
{
  char *value;

  arg++;
  /*
  while (env[i])
  {
    if (!ft_strncmp(arg, env[i], ft_strlen(arg)))
      return (env[i] + ft_strlen(arg) + 1);
    i++;
  }
  */
  value = get_exported_arg_value(arg, NULL, 0);
  if (value)
    return (value);
  else
    return (NULL);
}

int add_node(t_list **dest, t_list *node)
{
  char *content;
  t_list *new_node;

  content = ft_strdup(node->content);
  if (!content)
    return (1);
  new_node = ft_lstnew(content);
  if (!new_node)
    return (free(content), 1);
  new_node->is_op = node->is_op;
  new_node->fd = node->fd;
  new_node->mask = node->mask;
  ft_lstadd_back(dest, new_node);
  return (0);
}

t_list *convert_arr_to_list(char **arr)
{
  int i;
  t_list *new;
  t_list *node;
  
  new = NULL;
  i = 0;
  while (arr[i])
  {
    node = ft_lstnew(arr[i]);
    if (!node)
      return (ft_lstclear(&new, &do_nothing), NULL);
    ft_lstadd_back(&new, node);
    i++;
  }
  return (new);
}

void do_nothing(void *arg)
{
  (void) arg;
}

void append_list(t_list *source, t_list **dest, char op)
{
  t_list *tmp;

  while (source)
  {
    tmp = source;
    source = source->next;
    tmp->next = NULL;
    tmp->is_op = op;
    ft_lstadd_back(dest, tmp);
  }
}

int lst_add_env_arg(t_list **dest, t_list *node, char *value)
{
  char **arr;
  char *start;
  char *end;
  char *tmp;
  t_list *new_lst;
  
  arr = ft_split(value, ' ');
  if (!arr)
    return (1);
  start = ft_substr(node->content, 0, node->mask - ft_strchr(node->mask, '1'));
  end = ft_substr(ft_strrchr(node->content, '0'), 0, ft_strlen(ft_strrchr(node->content, '0')));
  if (!start || !end)
    return (free_2d_arr((void **) arr), perror("malloc"), free(start), free(end), 1);
  tmp = arr[0];
  arr[0] = ft_strjoin(arr[0], start);
  if (!arr[0])
    return (perror("malloc"), free_2d_arr((void **) arr), 1);
  free(tmp);
  tmp = arr[1];
  arr[1] = ft_strjoin(end, arr[1]);
  if (!arr[1])
    return (perror("malloc"), free_2d_arr((void **) arr), 1);
  free(tmp);
  new_lst = convert_arr_to_list(arr);
  if (!new_lst)
    return (free_2d_arr((void **)arr), 1);
  append_list(new_lst, dest, '\'');
  free(arr);
  return (0);
}

// allocs: new
// frees lst on success
int expand_args(t_list **lst)
{
  t_list *tmp;
  char *arg;
  char *value;
  t_list *new;

  tmp = *lst;
  while (tmp)
  {
    if (tmp->mask)
    {
      arg = get_masked_portion(tmp->content, tmp->mask);
      if (!arg)
        return (ft_lstclear(&new, &free), 1);
      value = get_env_value(arg);
      if (value)
      {
        if (lst_add_env_arg(&new, tmp, value))
          return (ft_lstclear(&new, &free), 1);
      }
    }
    else
    {
      if (add_node(&new, tmp))
        return (ft_lstclear(&new, &free), perror("malloc"), 1);
    }
    tmp = tmp->next;
  }
  *lst = new;
  return (0);
}
