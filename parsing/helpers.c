

#include "minishell.h"

void lst_remove_node(t_list **lst, t_list *node)
{
  t_list *tmp;

  tmp = *lst;
  if (tmp == node)
  {
    *lst = node->next;
    ft_lstdelone(node, &free);
  }
  while (tmp->next)
  {
    if (tmp->next == node)
    {
      tmp->next = node->next;
      ft_lstdelone(node, &free);
      return ;
    }
    tmp = tmp->next;
  }
}

int is_wildcard(t_list *node)
{
  if (ft_strchr(node->content, '*') && !node->is_op)
    return (1);
  else
    return (0);
}


int is_space(t_list *node)
{
  if (!strncmp(node->content, " ", 2) && !node->is_op)
    return (1);
  else
    return (0);
}

void del_spaces(t_list **lst)
{
  t_list *tmp;
  t_list *tmp2;

  tmp = *lst;
  while (tmp)
  {
    tmp2 = tmp->next;
    if (is_space(tmp))
      lst_remove_node(lst, tmp);
    tmp = tmp2;
  }
}

int new_and_add(t_list **head, void *content)
{
  char *duped_content;
  t_list *new;

  duped_content = ft_strdup(content);
  if (!duped_content)
    return (1);
  new = ft_lstnew(duped_content);
  if (!new)
    return (free(duped_content), 1);
  ft_lstadd_back(head, new);
  return (0);
}

// allocs: arr
char **convert_list_to_arr(t_list *lst)
{
  int len;
  char **arr;
  int i;

  len = ft_lstsize(lst);
  arr = (char **) malloc(sizeof(char *) * (len + 1));
  if (!arr)
    return (NULL);
  i = 0;
  while (i < len)
  {
    arr[i] = (char *) lst->content;
    lst = lst->next;
    i++;
  }
  arr[i] = NULL;
  return (arr);
}

t_list *copy_lst(t_list *lst)
{
  char *content;
  t_list *new;
  t_list *node;

  new = NULL;
  while (lst)
  {
    content = ft_strdup(lst->content);
    if (!content)
      return (ft_lstclear(&new, &free), NULL);
    node = ft_lstnew(content);
    if (!node)
      return (ft_lstclear(&new, &free), free(content), NULL);
    node->is_op = lst->is_op;
    ft_lstadd_back(&new, node);
    lst = lst->next;
  }
  return (new);
}
