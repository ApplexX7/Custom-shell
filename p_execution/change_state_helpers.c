/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_state_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:22:48 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/29 17:24:57 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	input_files(t_tree *node)
{
	t_list	*current;
	int		fd_in;

	node->fd = dup(STDIN_FILENO);
	if (node->fd == -1)
		return (-1);
	current = node->input_files;
	while (current->next)
	{
		if (handle_ambiguous_redirection(current))
			return (-1);
		fd_in = open_files(current->content, 1);
		if (fd_in == -1)
			return (-1);
		ft_close(fd_in);
		current = current->next;
	}
	if (handle_ambiguous_redirection(current))
		return (-1);
	fd_in = open_files(current->content, 1);
	if (fd_in == -1)
		return (-1);
	if (dup_input(fd_in))
		return (1);
	return (0);
}

int	ouput_files_open(t_tree *root, t_list *current, int fd_out)
{
	if (handle_ambiguous_redirection(current))
		return (-1);
	if (root->open_mod == O_TRUNC)
		fd_out = open_files(current->content, 2);
	else if (root->open_mod == O_APPEND)
		fd_out = open_files(current->content, 3);
	if (fd_out == -1)
		return (-1);
	if (dup_output(fd_out))
		return (1);
	ft_close(fd_out);
	return (0);
}

int	output_files(t_tree *root)
{
	t_list	*current;
	int		fd_out;

	root->out_fd = dup(STDOUT_FILENO);
	if (root->out_fd == -1)
		return (1);
	current = root->output_files;
	while (current->next)
	{
		if (handle_ambiguous_redirection(current))
			return (-1);
		if (root->open_mod == O_TRUNC)
			fd_out = open_files(current->content, 2);
		else if (root->open_mod == O_APPEND)
			fd_out = open_files(current->content, 3);
		if (fd_out == -1)
			return (1);
		ft_close(fd_out);
		current = current->next;
	}
	if (ouput_files_open(root, current, fd_out))
		return (1);
	return (0);
}
