/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:05:51 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/17 15:05:58 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int expand_in_herdoc(char *str, int fd)
{
	t_list *lst;

	lst = split_tokens(str);
	if (!lst)
		return (1);
	// if (expand_args(&lst))
	// 	return (1);
	while (lst)
	{
		ft_putstr_fd(lst->content, fd);
		lst = lst->next;
	}
	ft_putchar_fd('\n', fd);
	ft_lstclear(&lst, &free);
	return (0);
}

void create_herdoc(char *limite, int *fd)
{
	char *str;
	char *tmp;

	tmp = limite;
	limite = ft_strjoin(limite, "\n");
	free(tmp);
	if (!limite)
		exit(0);
	ft_close(fd[0]);
	while (1)
	{
		write(1, "here_doc> ", 10);
		str = get_next_line(0);
		if (!str)
			exit(0);
		if (!ft_strncmp(str, limite, ft_strlen(str)))
		{
			free(str);
			ft_close(fd[1]);
			exit(0);
		}
		expand_in_herdoc(str, fd[1]);
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
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		create_herdoc(limite, fdpipe);
	}
	waitpid(pid, NULL, 0);
	manage_fds(fdpipe[1], CAPTURE);
	ft_close(fdpipe[1]);
	manage_fds(fdpipe[0], CAPTURE);
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
		else
			current->fd = 0;
		current = current->next;
	}
	return (0);
}

int open_file(char *str, int red)
{
	int fd = -1;

	if (red == 0)
		fd = ft_open(str, O_RDONLY, 0644);
	else if (red == 1)
		fd = ft_open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (red == 2)
		fd = ft_open(str, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Error ");
		return (-1);
	}
	return (fd);
}
