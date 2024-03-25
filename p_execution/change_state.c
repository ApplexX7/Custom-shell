/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:28:03 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/25 16:46:24 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void set_back_io(int input, int output)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		perror("dup");
		return ;
	}
	if (input != 0)
		close(input);
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		perror("dup");
		return ;
	}
	if (output != 1)
		close(output);
}

int dup_input(int fd_in)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2 :");
		return (1);
	}
	close(fd_in);
	return (0);
}

int input_files(t_tree *node)
{
	t_list *current;
	int fd_in;

	node->fd = dup(STDIN_FILENO);
	if (node->fd == -1)
		return (-1);
	current = node->input_files;
	while (current->next)
	{
		if (expand_args(&current))
			return (-1);
		fd_in = open_files(current->content, 1);
		if (fd_in == -1)
			return (-1);
		close(fd_in);
		current = current->next;
	}
	fd_in = open_files(current->content, 1);
	if (fd_in == -1)
		return (-1);
	if (dup_input(fd_in))
		return (1);
	return (0);
}

int dup_output(int fd_out)
{
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2 :");
		return (1);
	}
	close(fd_out);
	return (0);
}

int output_files(t_tree *root)
{
	t_list *current;
	int fd_out;

	root->out_fd = dup(STDOUT_FILENO);
	if (root->out_fd == -1)
		return (1);
	current = root->output_files;
	// if (expand_args(&current))
	// 		return (-1);
	while (current->next)
	{
		if (root->open_mod == O_TRUNC)
			fd_out = open_files(current->content, 2);
		else if (root->open_mod == O_APPEND)
			fd_out = open_files(current->content, 3);
		if (fd_out == -1)
			return (1);
		close(fd_out);
		current = current->next;
	}
	if (root->open_mod == O_TRUNC)
		fd_out = open_files(current->content, 2);
	else if (root->open_mod == O_APPEND)
		fd_out = open_files(current->content, 3);
	if (fd_out == -1)
		return (-1);
	if (dup_output(fd_out))
		return (1);
	return (0);
}

int	ft_dup_parent(t_tree *root)
{
	int fd_out = 1;
	int fd_in = 0;

	if (root->input_files != NULL)
	{
		if (input_files(root))
			return (1);
	}
	else if (root->fd != 0)
	{
		fd_in = root->fd;
		root->fd = dup(STDIN_FILENO);
		if (dup_input(fd_in))
			return (1);
	}
	if (root->output_files != NULL)
	{
		if (output_files(root))
			return (1);
	}
	else if (root->out_fd != 1)
	{
		fd_out = root->out_fd;
		root->out_fd = dup(STDOUT_FILENO);
		if (dup_output(fd_out))
			return (1);
	}
	return (0);
}
