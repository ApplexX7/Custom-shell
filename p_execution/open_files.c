/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:25:52 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/25 16:06:06 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	open_files(char *file_name, int level)
{
	int fd = -1;

	if (level == 1)
		fd = ft_open(file_name, O_RDONLY, 0644);
	else if (level == 2)
		fd = ft_open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (level == 3)
		fd = ft_open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("fd :");
		return(-1);
	}
	return (fd);
}

void dup_iofile(int fd_in, int fd_out)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2--in :");
		exit(errno);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2-- out:");
		exit(errno);
	}
  	manage_fds(0, CLOSE_ALL);
}

int set_file_io(t_tree *content)
{
	int fd_in;
	int fd_out;

	if (content->input_file != NULL)
	{
		fd_in = open_files(content->input_file, 1);
		content->fd =  fd_in;
	}
	// else if (content->input_file == NULL)
	// 	fd_in = content->fd;
	if (content->output_file != NULL)
	{
		fd_out = open_files(content->output_file, 2);
		content->out_fd = fd_out;
	}
	// else if (content->output_file == NULL)
	// 	fd_out = content->out_fd;
	if (content->node->content)
	{
		dup_iofile(content->fd, content->out_fd);
		return (0);
	}
	return (1);
}
