

#include "minishell.h"

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

// malloc: tmp, zeros
int set_ones_arr(char *str, char *mask, char ***ones)
{
  char *tmp;
  int i;

  tmp = ft_strdup(mask);
  if (!tmp)
    return (perror("malloc"), 1);
  i = 0;
  while (tmp[i])
  {
    if (tmp[i] == '1')
      tmp[i] = str[i];
    i++;
  }
  *ones = ft_split(tmp, '0');
  free(tmp);
  if (!(*ones))
    return (perror("malloc"), 1);
  return (0);
}

// malloc: tmp, zeros
int set_zeros_arr(char *str, char *mask, char ***zeros)
{
  char *tmp;
  int i;

  tmp = ft_strdup(mask);
  if (!tmp)
    return (perror("malloc"), 1);
  i = 0;
  while (tmp[i])
  {
    if (tmp[i] == '0')
      tmp[i] = str[i];
    i++;
  }
  *zeros = ft_split(tmp, '1');
  free(tmp);
  if (!(*zeros))
    return (perror("malloc"), 1);
  return (0);
}

// arr should be null terminated
int arr_size(char **arr)
{
  int i;

  i = 0;
  while (arr[i])
    i++;
  return (i);
}

int fil_split_arr(t_list **splited, char **zeros, char **ones, char *mask)
{
  int i;
  int j;
  char current;

  i = 0;
  j = 0;
  while (zeros[i] || ones[j])
  {
    current = *mask;
    if (current == '0' && new_and_add(splited, zeros[i++], '\''))
      return (1);
    else if (current == '1' && new_and_add(splited, ones[j++], 0))
      return (1);
    while (*mask == current)
      mask++;
  }
  return (0);
}

// allocs: zeros, ones
t_list *get_splited_list(char *str, char *mask)
{
  char **zeros;
  char **ones;
  t_list *splited;
  
  if (set_zeros_arr(str, mask, &zeros))
    return (NULL);
  if (set_ones_arr(str, mask, &ones))
    return (free_2d_arr((void **) zeros), NULL);
  splited = NULL;
  if (fil_split_arr(&splited, zeros, ones, mask))
    return (ft_lstclear(&splited, &free), free_2d_arr((void **) zeros), free_2d_arr((void **) ones), NULL);
  (free_2d_arr((void **) zeros), free_2d_arr((void **) ones));
  return (splited);
}

//000001111000111100000111110000111

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

int lst_add_env_arg(char *arg, t_list **dest)
{
  char **arr;
  t_list *new_lst;

  if (!arg)
    return (0);
  arr = ft_split(arg, ' ');
  if (!arr)
    return (1);
  new_lst = convert_arr_to_list(arr);
  if (!new_lst)
    return (free_2d_arr((void **)arr), 1);
  append_list(new_lst, dest, 0);
  free(arr);
  return (0);
}

/*
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
*/

// allocs: new
int combine_expand_list(t_list **lst)
{
  t_list *new;
  t_list *tmp;

  new = NULL;
  tmp = *lst;
  while (tmp)
  {
    if ((!tmp->is_op && tmp->next && tmp->next->is_op) || (tmp->next && !tmp->next->is_op && tmp->is_op))
    {
      if (join_and_add(&new, tmp, tmp->next->next))
        return (ft_lstclear(&new, &free), 1);
      tmp = tmp->next;
    }
    else
    {
      if (add_node(&new, tmp))
        return (ft_lstclear(&new, &free), perror("malloc"), 1);
    }
    tmp = tmp->next;
  }
  ft_lstclear(lst, &free);
  *lst = new;
  return (0);
}

// allocs: new
int expand(t_list **lst)
{
  t_list *new;
  t_list *tmp;

  new = NULL;
  tmp = *lst;
  while (tmp)
  {
    if (!tmp->is_op)
    {
      if (lst_add_env_arg(get_env_value(tmp->content), &new))
        return (ft_lstclear(&new, &free), 1);
    }
    else
    {
      if (add_node(&new, tmp))
        return (ft_lstclear(&new, &free), perror("malloc"), 1);
    }
    tmp = tmp->next;
  }
  ft_lstclear(lst, &free);
  *lst = new;
  return (0);
}

// allocs: splited
int expand_and_add(t_list *node, t_list **dest)
{
  t_list *splited;

  splited = get_splited_list(node->content, node->mask);
  if (!splited)
    return (1);
  if (expand(&splited))
    return (ft_lstclear(&splited, &free), 1);
  if (combine_expand_list(&splited))
    return (ft_lstclear(&splited, &free), 1);
  //print_ouput(splited);
  append_list(splited, dest, '\'');
  return (0);
}

// allocs: new
// frees lst on success
int expand_args(t_list **lst)
{
  t_list *tmp;
  t_list *new;

  tmp = *lst;
  new = NULL;
  while (tmp)
  {
    if (tmp->mask)
    {
      if (expand_and_add(tmp, &new))
        return (ft_lstclear(&new, &free), 1);
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
