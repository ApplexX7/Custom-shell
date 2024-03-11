/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:28:03 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/11 18:27:07 by mohilali         ###   ########.fr       */
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
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		perror("dup");
		return ;
	}
}

int	ft_dup_parent(t_tree *root)
{
	int fd_out = 1;
	int fd_int = 0;

	if (root->input_file != NULL)
	{
		root->fd = dup(STDIN_FILENO);
		if (root->fd == -1)
			return (-1);
		fd_int = open_files(root->input_file, 1);
		if (fd_int == -1)
			perror("Errorww");
	}
	else if (root->fd != 0)
	{
		fd_int = root->fd;
		root->fd = dup(STDIN_FILENO);
	}
	if (root->output_file != NULL)
	{
		root->out_fd = dup(STDOUT_FILENO);
		if (root->out_fd == -1)
			return (-1);
		if (root->open_mod == O_APPEND)
			fd_out = open_files(root->output_file, 2);
		else
			fd_out = open_files(root->output_file, 2);
		if (fd_out == -1)
			return (-1);
	}
	else if (root->out_fd != 0)
	{
		fd_out = root->out_fd;
		root->out_fd = dup(STDOUT_FILENO);
	}
	if (dup2(fd_int, STDIN_FILENO) == -1)
	{
		perror("dup");
		return (1);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup");
		return (1);
	}
	if (fd_int != 0)
		ft_close(fd_int);
	if (fd_out != 1)
		ft_close(fd_out);
	return (0);
}
