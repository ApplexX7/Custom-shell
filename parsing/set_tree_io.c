

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

  if (lst && is_open_parenth(lst))
  {
    level = 0;
    lst = lst->next;
    while (lst)
    {
      if (is_open_parenth(lst))
        level++;
      else if (is_close_parenth(lst))
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
  else if (!ft_strncmp(lst->content, "<<", 3) && !lst->is_op)
    return (1);
  else
    return (0);
}

int is_output_redirect(t_list *lst)
{
  if (!ft_strncmp(lst->content, ">" ,2) && !lst->is_op)
    return (1);
  else if (!ft_strncmp(lst->content, ">>" ,3) && !lst->is_op)
    return (1);
  else
    return (0);
}

int is_herdoc(t_list *lst)
{
  if (!ft_strncmp(lst->content, ">>", 3) || !ft_strncmp(lst->content, "<<", 3))
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
      free(node->input_file);
      if (is_herdoc(start))
      {
        node->input_file = NULL;
        node->fd = start->fd;
      }
      else
      {
        node->input_file = ft_strdup(start->next->content);
        if (node->input_file == NULL)
          return (write(2, "Malloc Failure\n", 15), 1);
        node->fd = 0;
      }
    }
    else if (is_output_redirect(start))
    {
      free(node->output_file);
      if (is_herdoc(start))
      {
        node->output_file = NULL;
        node->fd = start->fd;
      }
      else
      {
        node->output_file = ft_strdup(start->next->content);
        if (node->output_file == NULL)
          return (write(2, "Malloc Failure\n", 15), 1);
        node->fd = 0;
      }
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
  node->fd = 0;
  node->input_file = NULL;
  node->output_file = NULL;
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
