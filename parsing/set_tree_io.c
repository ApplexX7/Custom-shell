

#include "minishell.h"

/*
typedef struct s_tree
{
    t_list *node;
    struct s_tree *left;
    struct s_tree *right;
    int input;
    int output;

} t_tree;
*/

t_list *check_combined_redirection(t_list *lst)
{
  int level;

  if (lst && !ft_strncmp(lst->content, "(", 2) && !lst->is_op)
  {
    level = 0;
    lst = lst->next;
    while (lst)
    {
      if (!ft_strncmp(lst->content, "(", 2) && !lst->is_op)
        level++;
      else if (!ft_strncmp(lst->content, ")", 2) && !lst->is_op)
      {
        if (level == 0)
          return (lst->next);
        else
          level--;
      }
      lst = lst->next;
    }
  }
  return (NULL);
}

int is_redirect_op(t_list *lst)
{
  if (is_input_redirect(lst))
    return (1);
  else if (is_output_redirect(lst))
    return (1);
  else
    return (0);
}

int is_input_redirect(t_list *lst)
{
  if (!ft_strncmp(lst->content, "<" ,2) && !lst->is_op)
    return (1);
  else if (!ft_strncmp(lst->content, "<<" ,2) && !lst->is_op)
    return (1);
  else
    return (0);
}

int is_output_redirect(t_list *lst)
{
  if (!ft_strncmp(lst->content, ">" ,2) && !lst->is_op)
    return (1);
  else if (!ft_strncmp(lst->content, ">>" ,2) && !lst->is_op)
    return (1);
  else
    return (0);
}

int set_io(t_tree *node, t_list *start)
{
  while (start)
  {
    if (is_input_redirect(start))
    {
      if (node->input != 0)
      {
        if (close(node->input))
          return (write(2, "error closing fd\n", 17), 1);
      }
      node->input = start->fd;
    }
    else if (is_output_redirect(start))
    {
      if (node->output != 0)
      {
        if (close(node->output))
          return (write(2, "error closing fd\n", 17), 1);
      }
      node->output = start->fd;
    }
    start = start->next->next;
  }
  return (0);
}

void remove_redirections(t_tree *node, t_list *start)
{
  t_list *tmp;
  t_list *head;

  head = node->node;
  while (start)
  {
    tmp = start->next;
    lst_remove_node(&head, start);
    start = tmp;
  }
  node->node = head;
}

int tree_set_io(t_tree *node)
{
  t_list *tmp;
  t_list *tmp2;

  if (!node)
    return (0);
  node->input = 0;
  node->output = 1;
  tmp = check_combined_redirection(node->node);
  if (!tmp)
    return (0);
  tmp2 = tmp;
  while (tmp && is_redirect_op(tmp))
    tmp = tmp->next->next;
  if (tmp != NULL)
    return (0);
  if (set_io(node, tmp2))
    return (1);
  remove_redirections(node, tmp2);
  return (0);
}
