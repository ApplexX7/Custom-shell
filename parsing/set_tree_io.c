/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tree_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:59:39 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/29 15:05:05 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input_redirect(t_tree *node, t_list *start, t_list **input_files)
{
	if (node->fd)
		ft_close(node->fd);
	free(node->input_file);
	if (is_herdoc(start))
	{
		node->input_file = NULL;
		node->fd = start->fd;
	}
	else
	{
		if (add_node(input_files, skip_spaces(start->next)))
			return (perror("handle_input_redirect: malloc"), 1);
		node->fd = 0;
	}
	return (0);
}

int	handle_ouput_redirect(t_tree *node, t_list *start, t_list **output_files)
{
	if (node->out_fd != 1)
		ft_close(node->fd);
	free(node->output_file);
	if (is_herdoc(start))
	{
		if (add_node(output_files, skip_spaces(start->next)))
			return (perror("handle_ouput_redirect: malloc"), 1);
		node->out_fd = 1;
		node->open_mod = O_APPEND;
	}
	else
	{
		if (add_node(output_files, skip_spaces(start->next)))
			return (perror("set_io: malloc"), 1);
		node->out_fd = 1;
		node->open_mod = O_TRUNC;
	}
	return (0);
}

int	set_io(t_tree *node, t_list *start, t_list **input_files,
		t_list **output_files)
{
	while (start)
	{
		if (is_input_redirect(start))
		{
			if (handle_input_redirect(node, start, input_files))
				return (1);
		}
		else if (is_output_redirect(start))
		{
			if (handle_ouput_redirect(node, start, output_files))
				return (1);
		}
		start = skip_spaces(skip_spaces(start->next)->next);
	}
	return (0);
}

static void	init_arguments(t_tree *node)
{
	node->fd = 0;
	node->out_fd = 1;
	node->input_files = NULL;
	node->output_files = NULL;
	node->input_file = NULL;
	node->output_file = NULL;
}

// allocs: files_list, output_files
int	tree_set_io(t_tree *node)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*input_files;
	t_list	*output_files;

	if (!node)
		return (0);
	input_files = NULL;
	output_files = NULL;
	init_arguments(node);
	tmp = check_combined_redirection(node->node);
	if (!tmp)
		return (0);
	tmp2 = skip_spaces(tmp);
	while (skip_spaces(tmp) && is_redirect_op(skip_spaces(tmp)))
		tmp = skip_spaces(skip_spaces(tmp)->next)->next;
	if (skip_spaces(tmp) != NULL)
		return (0);
	if (set_io(node, tmp2, &input_files, &output_files))
		return (ft_lstclear(&input_files, &free), ft_lstclear(&output_files,
				&free), 1);
	remove_redirections(node, tmp2);
	node->input_files = input_files;
	node->output_files = output_files;
	return (0);
}
