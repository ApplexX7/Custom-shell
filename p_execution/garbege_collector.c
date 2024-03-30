/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbege_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:58:20 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/30 03:26:50 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	wait_for_childs(t_list **head, int *last_status)
{
	t_list	*current;
	int		terminastatus;

	current = *head;
	while (current)
	{
		if (waitpid(*(int *)current->content, last_status, 0) == -1)
			return (ft_lstclear(head, &free), *head = NULL, 1);
		if (WIFSIGNALED(*last_status))
			terminastatus = WTERMSIG(*last_status);
		if (terminastatus == SIGINT)
			ft_memset(last_status, EXIT_TERMSIGINT, 2);
		else if (terminastatus == SIGQUIT)
			ft_memset(last_status, EXIT_TERMSIGQUIT, 2);
		current = current->next;
	}
	ft_lstclear(head, &free);
	*head = NULL;
	return (0);
}

int	manage_pid(int pid, t_pid_action action, int *last_status)
{
	static t_list	*head = NULL;
	t_list			*current;
	int				*pidarr;

	current = NULL;
	if (action == CAPTURED)
	{
		pidarr = malloc(sizeof(int));
		*pidarr = pid;
		current = ft_lstnew(pidarr);
		if (current)
			ft_lstadd_back(&head, current);
		else
		{
			ft_lstclear(&head, &free);
			current = NULL;
		}
	}
	else if (action == WAIT)
	{
		if (wait_for_childs(&head, last_status))
			return (1);
	}
	return (0);
}

int	ft_open(char *file, int mode, int perms)
{
	int	fd;

	fd = open(file, mode, perms);
	manage_fds(fd, CAPTURE);
	return (fd);
}

int	ft_close(int fd)
{
	if (manage_fds(fd, CLOSE))
		return (-1);
	else
		return (0);
}
