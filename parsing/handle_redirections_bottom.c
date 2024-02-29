

#include "minishell.h"

int set_single_io(t_tree *node, t_list *pos)
{
  if (is_input_redirect(pos))
  {
    if (node->input != 0)
    {
      if (close(node->input))
        return (write(2, "error closing fd\n", 17), 1);
    }
    node->input = pos->fd;
  }
  else if (is_output_redirect(pos))
  {
    if (node->output != 1)
    {
      if (close(node->output))
        return (write(2, "error closing fd\n", 17), 1);
    }
    node->output = pos->fd;
  }
  return (0);
}

// TODO: replace it with remove_redirections
void remove_redirectiosn2(t_tree *node)
{
  t_list *head;
  t_list *tmp;
  t_list *tmp2;

  head = node->node;
  tmp = node->node;
  while (tmp)
  {
    if (is_redirect_op(tmp))
    {
      tmp2 = tmp->next->next;
      lst_remove_node(&head, tmp->next);
      lst_remove_node(&head, tmp);
      tmp = tmp2;
    }
    else
      tmp = tmp->next;
  }
  node->node = head;
}

int handle_redirections_bottom(t_tree *node)
{
  t_list *head;
  t_list *tmp;

  head = node->node;
  tmp = head;
  while (tmp)
  {
    if (is_redirect_op(tmp))
    {
      if (set_single_io(node, tmp))
        return (1);
      tmp = tmp->next->next;
    }
    else
      tmp = tmp->next;
  }
  remove_redirectiosn2(node);
  return (0);
}
