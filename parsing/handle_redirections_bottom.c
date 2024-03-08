

#include "minishell.h"



int set_single_io(t_tree *node, t_list *pos)
{
	if (is_input_redirect(pos))
	{
    if (node->fd)
      close(node->fd);
    free(node->input_file);
    node->input_file = NULL;
		if (is_herdoc(pos))
			node->fd = pos->fd;
		else
		{
			node->fd = open(pos->next->content, O_RDONLY, 0644);
			if (node->fd == -1)
				return (ft_putstr_fd("set_single_io: open error\n", 2), 1);
		}
	}
	else if (is_output_redirect(pos))
	{
    if (node->out_fd != 1)
      close(node->out_fd);
		free(node->output_file);
    node->output_file = NULL;
		if (is_herdoc(pos))
		{
			node->fd = pos->fd;
      node->open_mod = O_WRONLY | O_APPEND; // TODO: useless maybe
		}
		else
		{
			node->out_fd = open(pos->next->content, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (node->out_fd == -1)
				return (ft_putstr_fd("set_single_io: open error\n", 2), 1);
      node->open_mod = O_WRONLY | O_TRUNC; // TODO: useless maybe
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
