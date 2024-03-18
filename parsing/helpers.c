

#include "minishell.h"

void lst_remove_node(t_list **lst, t_list *node)
{
  t_list *tmp;

  tmp = *lst;
  if (tmp == node)
  {
    *lst = node->next;
    ft_lstdelone(node, &free);
    return ;
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

int new_and_add(t_list **head, void *content, char is_op)
{
  char *duped_content;
  t_list *new;

  duped_content = ft_strdup(content);
  if (!duped_content)
    return (1);
  new = ft_lstnew(duped_content);
  if (!new)
    return (free(duped_content), 1);
  new->is_op = is_op;
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

void free_2d_arr(void **arr)
{
  int i;

  i = 0;
  while (arr[i])
  {
    free(arr[i]);
    i++;
  }
  free(arr);
}

// allocs: new
char *join_list(t_list *lst)
{
  char *new;
  char *tmp;

  new = malloc(1);
  if (!new)
    return (NULL);
  new[0] = '\0';
  while (lst)
  {
    tmp = new;
    new = ft_strjoin(new, lst->content);
    free(tmp);
    if (!new)
      return (NULL);
    lst = lst->next;
  }
  return (new);
}

int should_join_mask(t_list *start, t_list *end)
{
  int join;

  join = 0;
  while (start != end)
  {
    if (start->mask)
      join = 1;
    start = start->next;
  }
  return (join);
}

//allocs: tmp, tmp3
int join_mask(t_list *start, t_list *end, t_list *dest)
{
  char *tmp;
  char *tmp2;
  char *tmp3;

  tmp = NULL;
  if (should_join_mask(start, end))
  {
    while (start != end)
    {
      if (!start->mask)
      {
        tmp2 = ft_strdup(start->content);
        full_withzero(&tmp2);
      }
      else
      {
        tmp2 = start->mask;
        start->mask = NULL;
      }
      if (!tmp2)
        return (free(tmp), perror("join_mask"), 1);
      tmp3 = tmp;
      tmp = ft_strjoin(tmp, tmp2);
      free(tmp2);
      free(tmp3);
      if (!tmp)
        return (perror("join_mask"), 1);
      start = start->next;
    }
  }
  return (dest->mask = tmp, 0);
}

// allocs: str, new
// TODO: change this to have is_op passed as an arg
int join_and_add(t_list **dest, t_list *start, t_list *end)
{
  t_list *tmp;
  char *str;
  t_list *new;

  tmp = start;
  while (tmp->next != end)
    tmp = tmp->next;
  tmp->next = NULL;
  str = join_list(start);
  tmp->next = end;
  if (!str)
    return (1);
  new = ft_lstnew(str);
  if (!new)
    return (free(str), 1);
  new->is_op = 1;
  if (join_mask(start, end, new))
    return (ft_lstdelone(new, &free), 1);
  ft_lstadd_back(dest, new);
  return (0);
}

int is_open_parenth(t_list *node)
{
  if (!ft_strncmp(node->content, "(", 2) && !node->is_op)
    return (1);
  else
    return (0);
}

int is_close_parenth(t_list *node)
{
  if (!ft_strncmp(node->content, ")", 2) && !node->is_op)
    return (1);
  else
    return (0);
}

// note: only use in set_single_io
int is_herdoc(t_list *lst)
{
  if (!ft_strncmp(lst->content, ">>", 3) || !ft_strncmp(lst->content, "<<", 3))
    return (1);
  else
    return (0);
}

int min(int a, int b)
{
  if (a < b)
    return (a);
  else
    return (b);
}

int max(int a, int b)
{
  if (a > b)
    return (a);
  else
    return (b);
}

void swap(t_list *a, t_list *b)  
{  
  void *tmp;

  tmp = a->content;
  a->content = b->content;
  b->content = tmp;
}  

void bubbleSort(t_list *start)
{
  int swapped;
  t_list *ptr1;
  t_list *lptr;

  lptr = NULL;
  if (start == NULL)
    return;

  swapped = 1;
  while (swapped)
  {
    swapped = 0;
    ptr1 = start;

    while (ptr1->next != lptr) {
      if (ft_strncmp(ptr1->content, ptr1->next->content, max(ft_strlen(ptr1->next->content), ft_strlen(ptr1->content)) + 1) > 0)
      {
        swap(ptr1, ptr1->next);
        swapped = 1;
      }
      ptr1 = ptr1->next;
    }
    lptr = ptr1;
  }
}
