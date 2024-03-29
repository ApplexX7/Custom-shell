/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_bottom.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:31:45 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/28 18:09:24 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_input_redirection(t_tree *node, t_list *pos)
{
	if (node->fd)
		ft_close(node->fd);
	free(node->input_file);
	node->input_file = NULL;
	if (is_herdoc(pos))
		node->fd = pos->fd;
	else
	{
		node->fd = ft_open(pos->next->content, O_RDONLY, 0644);
		if (node->fd == -1)
			return (perror("open"), 1);
	}
	return (0);
}

static int	handle_ouput_redirection(t_tree *node, t_list *pos)
{
	if (node->out_fd != 1)
		ft_close(node->out_fd);
	free(node->output_file);
	node->output_file = NULL;
	if (is_herdoc(pos))
	{
		node->out_fd = ft_open(pos->next->content,
				O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (node->fd == -1)
			return (perror("open"), 1);
	}
	else
	{
		node->out_fd = ft_open(pos->next->content, O_WRONLY | O_TRUNC | O_CREAT,
				0644);
		if (node->out_fd == -1)
			return (perror("open"), 1);
	}
	return (0);
}

int	set_single_io(t_tree *node, t_list *pos)
{
	if (handle_ambiguous_redirection(pos->next))
		return (1);
	if (is_input_redirect(pos))
	{
		if (handle_input_redirection(node, pos))
			return (1);
	}
	else if (is_output_redirect(pos))
	{
		if (handle_ouput_redirection(node, pos))
			return (1);
	}
	return (0);
}

// TODO: replace it with remove_redirections
void	remove_redirectiosn2(t_tree *node)
{
	t_list	*head;
	t_list	*tmp;
	t_list	*tmp2;

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

int	handle_redirections_bottom(t_tree *node)
{
	t_list	*head;
	t_list	*tmp;

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
