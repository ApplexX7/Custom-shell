#include "minishell.h"

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

// spaces are usefull but after will be useless
int is_useless_token(t_list *node)
{
  if (!strncmp(node->content, "\'", 2) && !node->is_op)
    return (1);
  else if (!strncmp(node->content, "\"", 2) && !node->is_op)
    return (1);
  return (0);
}

int handle_consecutive_quotes(t_list *node)
{
  if (!node->next)
    return (0);
  else if (!strncmp(node->content, "'", 2) && !node->is_op && !strncmp(node->next->content, "'", 2) && !node->next->is_op)
    return (1);
  else if (!strncmp(node->content, "\"", 2) && !node->is_op && !strncmp(node->next->content, "\"", 2) && !node->next->is_op)
    return (1);
  else return (0);
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

  tmp = *lst;
  while (tmp)
  {
    if (is_space(tmp))
      lst_remove_node(lst, tmp);
    tmp = tmp->next;
  }
}

void del_useless_tokens(t_list **lst)
{
  t_list *tmp;

  tmp = *lst;
  while (tmp)
  {
    if (handle_consecutive_quotes(tmp))
    {
      tmp->is_op = ((char *)tmp->content)[0];
      ((char *)tmp->content)[0] = '\0';
    }
    else if (is_useless_token(tmp))
      lst_remove_node(lst, tmp);
    tmp = tmp->next;
  }
}

// allocs: str, new
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
  ft_lstadd_back(dest, new);
  return (0);
}


int skip_nonliterals(t_list *start, t_list **head, t_list **tmp)
{
  while (start && !start->is_op)
  {
    if (add_node(head, start))
      return (1);
    start = start->next;
  }
  *tmp = start;
  return (0);
}


t_list *skip_literals(t_list *start)
{
  while (start && start->is_op)
    start = start->next;
  return (start);
}

int is_breaking_token(t_list *node)
{
  if (!ft_strncmp(node->content, "<<", 3) && !node->is_op)
    return (1);
  else if (!ft_strncmp(node->content, ">>", 3) && !node->is_op)
    return (1);
  else if (!ft_strncmp(node->content, "|", 2) && !node->is_op)
    return (1);
  else if (!ft_strncmp(node->content, ">", 2) && !node->is_op)
    return (1);
  else if (!ft_strncmp(node->content, "<", 2) && !node->is_op)
    return (1);
  else if (!ft_strncmp(node->content, "||", 3) && !node->is_op)
    return (1);
  else if (!ft_strncmp(node->content, "&&", 3) && !node->is_op)
    return (1);
  else if (!strncmp(node->content, " ", 2) && !node->is_op)
    return (1);
  else if (ft_strchr(node->content, '*') && !node->is_op) // TODO: remove in mandatory
    return (1);
  return (0);
}

// allocs: new
// frees lst on success
int combine_lits_with_nonlists(t_list **lst)
{
  t_list *new;
  t_list *tmp;
  t_list *start;

  new = NULL;
  tmp = *lst;
  while (tmp)
  {
    if ((!is_breaking_token(tmp) && tmp->is_op == 0 && tmp->next && tmp->next->is_op != 0) || tmp->is_op)
    {
      start = tmp;
      while (tmp && !is_breaking_token(tmp))
        tmp = tmp->next;
      if (join_and_add(&new, start, tmp))
        return (ft_lstclear(&new, &free), 1);
    }
    else
    {
      if (add_node(&new, tmp))
        return (ft_lstclear(&new, &free), 1);
      tmp = tmp->next;
    }
  }
  ft_lstclear(lst, &free);
  *lst = new;
  return (0);
}

// allocs: new
// frees lst on success
// it deletes the quotes and combine the literals
int combine_list(t_list **lst)
{
  t_list *tmp;
  t_list *new;
  t_list *start;

  del_useless_tokens(lst);
  tmp = *lst;
  new = NULL;
  if (skip_nonliterals(tmp, &new, &tmp))
    return (ft_lstclear(&new, &free), 1);
  start = tmp;
  while (tmp)
  {
    tmp = skip_literals(tmp);
    if (join_and_add(&new, start, tmp))
      return (ft_lstclear(&new, &free), 1);
    if (skip_nonliterals(tmp, &new, &tmp))
      return (ft_lstclear(&new, &free), 1);
    start = tmp;
  }
  if (combine_lits_with_nonlists(&new))
    return (ft_lstclear(&new, &free), 1);
  ft_lstclear(lst, &free);
  *lst = new;
  return (0);
}

/*
int main(void)
{
  t_list *lst = NULL;
  t_list *first = ft_lstnew(ft_strdup("first"));
  t_list *mid = ft_lstnew(ft_strdup("mid"));
  t_list *end = ft_lstnew(ft_strdup("end"));

  ft_lstadd_back(&lst, first);
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, mid);
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, end);
  lst_remove_node(&lst, first);
  lst_remove_node(&lst, mid);
  lst_remove_node(&lst, end);
  printf("%s\n", join_list(lst));
}
*/

/*
int main(void)
{
  t_list *lst = NULL;
  t_list *first = ft_lstnew(ft_strdup("first"));
  t_list *mid = ft_lstnew(ft_strdup("mid"));
  t_list *end = ft_lstnew(ft_strdup("end"));

  ft_lstadd_back(&lst, first);
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, mid);
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, end);
  lst_remove_node(&lst, first);
  lst_remove_node(&lst, mid);
  lst_remove_node(&lst, end);
  print_ouput(lst);
}
*/
