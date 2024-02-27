/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:05:51 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/27 10:58:28 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void create_herdoc(char *limite, int *fd)
{
	char *str;

	close(fd[0]);
	while (1)
	{
		write(1, "here_doc> ", 10);
		str = get_next_line(0);
		if (!str)
			exit(0);
		if (!ft_strncmp(str, limite, ft_strlen(str) - 1))
		{
			free(str);
			close(fd[1]);
			exit(0);
		}
		ft_putstr_fd(str, fd[1]);
		free(str);
	}
}

int create_heredocchild(char *limite)
{
	int fdpipe[2];
	int pid;

	if (pipe(fdpipe) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
		create_herdoc(limite, fdpipe);
	waitpid(pid, NULL, 0);
	close(fdpipe[1]);
	return (fdpipe[0]);
}

int ft_open_herdocs(t_list *list)
{
	t_list *current;
	int fd;

	current = list;
	fd = 0;
	while (current)
	{
		if (!ft_strncmp(current->content, "<<", 3) && !current->is_op)
		{
			fd = create_heredocchild(current->next->content);
			if (fd == -1)
				return (1);
			current->fd = fd;			
		}
		current = current->next;
	}
	return (0);
}

int open_file(char *str, int red)
{
	int fd = -1;

	if (red == 0)
		fd = open(str, O_RDONLY);
	else if (red == 1)
		fd = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (red == 2)
		fd = open(str, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Error ");
		return (-1);
	}
	return (fd);
}

int open_redirections(t_list *current)
{
	int fd;
	if (!ft_strncmp(current->content, "<", 2) && !current->is_op)
	{
		printf("%s\n", (char *)current->next->content);
		fd = open_file(current->next->content, 0);
		if (fd == -1)
			return (-1);
		current->fd = fd;
	}
	if (!ft_strncmp(current->content, ">", 2) && !current->is_op)
	{
		fd = open_file(current->next->content, 1);
		if (fd == -1)
			return (-1);
		current->fd = fd;
	}
	if (!ft_strncmp(current->content, ">>", 3) && !current->is_op)
	{
		fd = open_file(current->next->content, 2);
		if (fd == -1)
			return (-1);
		current->fd = fd;
	}
	return (0);
}

int ft_open_redirections(t_list *lst)
{
	t_list *current;

	current = lst;
	while (current)
	{
		if (open_redirections(current) == -1)
			return (1);
		current = current->next;
	}
	return (0);
}
