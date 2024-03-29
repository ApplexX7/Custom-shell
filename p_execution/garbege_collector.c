/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbege_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:58:20 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/29 13:59:37 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

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
			if (fds[i] != 1 && fds[i] != 0)
			{
				if (close(fds[i]))
					return (1);
				fds[i] = 0;
			}
			i++;
		}
	}
	else if (action == CLOSE)
	{
		while (i < OPEN_MAX)
		{
			if (fds[i] == fd)
			{
				if (close(fds[i]) == -1)
					return (1);
				fds[i] = 0;
				return (0);
			}
			i++;
		}
	}
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
		current = head;
		while (current)
		{
			if (waitpid(*(int *)current->content, last_status, 0) == -1)
				return (ft_lstclear(&head, &free), head = NULL, 1);
			current = current->next;
		}
		ft_lstclear(&head, &free);
		head = NULL;
	}
	return (0);
}

// int manage_pid(int pid, t_pid_action action, int *last_status)
// {
// 	static int	pids[CHILD_MAX];
// 	static int	pid_index = 0;
// 	int			i;

// 	i = 0;
// 	if (action == CAPTURED && pid_index < CHILD_MAX)
// 	{
// 		pids[pid_index] = pid;
// 		pid_index++;
// 	}
// 	else if (action == WAIT)
// 	{
// 		while (i < pid_index)
// 		{
// 			if (waitpid(pids[i], last_status, 0) == -1)
// 				return (1);
// 			i++;
// 		}
// 		// while (waitpid(-1, NULL, 0) != -1)
// 		// ;
// 		pid_index = 0;
// 	}
// 	return (0);
// }

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
