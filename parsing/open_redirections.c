/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:05:51 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/29 14:27:10 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_lobal_sign_forherdoc;

void	sigquit2(int signo)
{
	(void)signo;
	rl_redisplay();
	return ;
}

int	expand_in_herdoc(t_list *current, char *str, int fd)
{
	t_list	*lst;

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

void	create_herdoc(t_list *current, int fd)
{
	char	*str;
	char	*tmp;
	char	*limite;

	tmp = ft_strdup(current->content);
	limite = ft_strjoin(tmp, "\n");
	free(tmp);
	if (!limite)
		exit(0);
	while (1)
	{
		str = readline("here_doc> ");
		if (!str)
			exit(0);
		if (!ft_strncmp(str, limite, ft_strlen(str)) && ft_strlen(str) == ft_strlen(limite))
		{
			free(str);
			ft_close(fd);
			exit(0);
		}
		expand_in_herdoc(current, str, fd);
		free(str);
	}
}

int	create_heredocchild(t_list *current)
{
	int	pid;
	int	fd;
	int	status;

	fd = ft_open("/tmp/herdoc.txt", O_CREAT | O_RDWR, 0644);
	if (fd == -1)
		return (-1);
	g_lobal_sign_forherdoc = 1;
	pid = fork();
	if (pid == -1)
		return (g_lobal_sign_forherdoc = 0, -1);
	else if (pid == 0)
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, &sigquit2),
			create_herdoc(current, fd));
	ft_close(fd);
	fd = ft_open("/tmp/herdoc.txt", O_RDWR, 0644);
	if (fd == -1)
		return (-1);
	unlink("/tmp/herdoc.txt");
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return (g_lobal_sign_forherdoc = 0, -1);
	manage_fds(fd, CAPTURE);
	return (g_lobal_sign_forherdoc = 0, fd);
}

int	ft_open_herdocs(t_list *list)
{
	t_list	*current;
	int		fd;

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
