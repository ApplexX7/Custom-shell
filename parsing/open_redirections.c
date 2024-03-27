/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:05:51 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/27 14:41:40 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int expand_in_herdoc(t_list *current ,char *str, int fd)
{
	t_list *lst;

	lst = split_tokens(str);
	if (!lst)
		return (1);
	if (!current->is_op)
		if (expand_herdoc(&lst))
			return (1);
	while (lst)
	{
		ft_putstr_fd(lst->content, fd);
		lst = lst->next;
	}
	ft_putchar_fd('\n', fd);
	ft_lstclear(&lst, &free);
	return (0);
}

void create_herdoc(t_list *current, int fd)
{
	char *str;
	char *tmp;
	char *limite;
	
	tmp = ft_strdup(current->content);
	limite = ft_strjoin(tmp, "\n");
	free(tmp);
	if (!limite)
		exit(0);
	while (1)
	{
		rl_catch_signals = 0;
		write(1, "here_doc> ", 10);
		str = get_next_line(0);
		if (!str)
			exit(0);
		if (!ft_strncmp(str, limite, ft_strlen(str)))
		{
			free(str);
			ft_close(fd);
			exit(0);
		}
		expand_in_herdoc(current ,str, fd);
		free(str);
	}
}

int create_heredocchild(t_list *current)
{
	int pid;
	int fd;
	int status;

	fd = open("/tmp/herdoc.txt", O_CREAT | O_RDWR, 0644);
	if (fd == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		// signal(SIGINT, SIG_DFL);
		create_herdoc(current, fd);
	}
	close(fd);
	fd = open("/tmp/herdoc.txt", O_RDWR, 0644);
	if (fd == -1)
		return (-1);
	unlink("/tmp/herdoc.txt");
	waitpid(pid,&status, 0);
	if (WIFSIGNALED(status))
		return (-1);
	manage_fds(fd, CAPTURE);
	return (fd);
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
			fd = create_heredocchild(current->next);
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

