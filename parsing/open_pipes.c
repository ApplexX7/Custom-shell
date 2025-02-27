/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:07:00 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/30 03:39:20 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tree_copy_output(char *output_file, int out_fd, t_tree *to)
{
	char	*new;

	if (!to)
		return (0);
	if (output_file)
	{
		new = ft_strdup(output_file);
		if (!new)
			return (1);
		free(to->output_file);
		to->output_file = new;
		to->out_fd = 1;
	}
	else
	{
		if (to->output_file)
			ft_close(out_fd);
		else
			to->out_fd = out_fd;
	}
	return (0);
}

int	tree_copy_input(char *input_file, int fd, t_tree *to)
{
	char	*new;

	if (!to)
		return (0);
	if (input_file)
	{
		new = ft_strdup(input_file);
		if (!new)
			return (1);
		free(to->input_file);
		to->input_file = new;
		to->fd = 0;
	}
	else
	{
		if (to->input_file || to->fd != 0)
			ft_close(fd);
		else
			to->fd = fd;
	}
	return (0);
}

int	open_pipes(t_tree *root, int *last_status)
{
	int	pip[2];

	if (!root)
		return (0);
	if (root->node && !ft_strncmp(root->node->content, "|", 2))
	{
		if (pipe(pip) == -1)
			return (write(2, "pipe: failed to create pipe\n", 28),
				ft_memset(last_status, 1, 2), 1);
		manage_fds(pip[0], CAPTURE);
		manage_fds(pip[1], CAPTURE);
		if (tree_copy_output(NULL, pip[1], root->left))
			return (write(2, "failed to copy tree output\n", 26), 1);
		if (tree_copy_input(NULL, pip[0], root->right))
			return (write(2, "failed to copy tree input\n", 25), 1);
		if (tree_copy_output(root->output_file, root->out_fd, root->right))
			return (write(2, "failed to copy tree input\n", 25), 1);
	}
	if (open_pipes(root->left, last_status))
		return (1);
	if (open_pipes(root->right, last_status))
		return (1);
	return (0);
}
