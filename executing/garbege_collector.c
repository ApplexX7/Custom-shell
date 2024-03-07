/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbege_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:58:20 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/06 16:27:35 by mohilali         ###   ########.fr       */
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
			if (close(fds[i]))
			{
				perror("Error :");
				return (1);
			}
			i++;
		}
		index = 0;
	}
	return (0);
}

int manage_pid(int pid, t_pid_action action)
{
	static int	pids[CHILD_MAX];
	static int	pid_index = 0;
	int			i;
	int status;

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
			waitpid(pids[i], &status, 0);
			i++;
		}
		pid_index = 0;
	}
	return (0);
}
