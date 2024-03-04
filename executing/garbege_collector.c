/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbege_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:58:20 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/04 19:40:56 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int manage_fds(int fd, t_fd_action action)
{
	static int 	fds[OPEN_MAX];
	static int 	index;
	int			i;

	index = 0;
	i = 0;
	if (action == CAPTURE)
	{
		fds[index] = fd;
		index++;
	}
	else if (action = CLOSE)
	{
		while (i < index)
		{
			if (close(fds[i]))
			{
				ft_hnalde_error(errno);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int manage_pid(int pid, t_pid_action action)
{
	static int	pids[CHILD_MAX];
	static int	pid_index;
	int			i = 0;
	int status;

	pid_index = 0;
	i = 0;
	if (action == CAPTURED)
	{
		pids[pid_index] = pid;
		pid_index++;
	}
	else if (action == WAIT)
	{
		while (i < index)
		{
			waitpid(pids[i], &status, 0);
			i++;
		}
	}
	return (0);
}
