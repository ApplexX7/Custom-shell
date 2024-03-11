/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbege_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:58:20 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/10 18:41:48 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int manage_fds(int fd, t_fd_action action)
{
	static int 	fds[OPEN_MAX];
	static int 	index = 0;
	int			i;

	i = 0;
	if (action == CAPTURE)
	{
		fds[index] = fd;
		index++;
	}
	else if (action == CLOSE)
	{
		while (i < index)
		{
			close(fds[i]);
			i++;
		}
		index = 0;
	}
	return (0);
}

int manage_pid(int pid, t_pid_action action, int *last_status)
{
	static int	pids[CHILD_MAX];
	static int	pid_index = 0;
	int			i;

	i = 0;
	if (action == CAPTURED)
	{
		pids[pid_index] = pid;
		pid_index++;
	}
	else if (action == WAIT)
	{
		while (i < pid_index)
		{
			if (waitpid(pids[i], last_status, 0) == -1)
				return (1);
			i++;
		}
		pid_index = 0;
	}
	return (0);
}
