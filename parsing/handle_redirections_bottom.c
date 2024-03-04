

#include "minishell.h"

int set_single_io(t_tree *node, t_list *pos)
{
	if (is_input_redirect(pos))
	{
		free(node->input_file);
		if (is_herdoc(pos))
		{
			node->input_file = NULL;
			node->fd = pos->fd;
		}
		else
		{
			node->input_file = ft_strdup(pos->next->content);
			if (node->input_file == NULL)
				return (write(2, "Malloc Failure\n", 15), 1);
			node->fd = 0;
		}
	}
	else if (is_output_redirect(pos))
	{
		free(node->output_file);
		if (is_herdoc(pos))
		{
			node->output_file = NULL;
			node->fd = pos->fd;
		}
		else
		{
			node->output_file = ft_strdup(pos->next->content);
			if (node->output_file == NULL)
				return (write(2, "Malloc Failure\n", 15), 1);
			node->out_fd = 1;
		}
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
