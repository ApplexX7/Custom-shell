/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbege_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:58:20 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/09 10:22:13 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int manage_fds(int fd, t_fd_action action)
{
	static int 	fds[OPEN_MAX];
	int			i;

	i = 0;
	if (action == CAPTURE)
	{
    while (fds[i] != 0 && i < OPEN_MAX)
      i++;
    if (i < OPEN_MAX)
      fds[i] = fd;
	}
	else if (action == CLOSE_ALL)
	{
		while (i < OPEN_MAX)
		{
      if (fds[i] != 1 && fds[i] != 0)
      {
        if (close(fds[i]))
        {
          perror("Error :");
          return (1);
        }
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
          return (perror("close"), 1);
        fds[i] = 0;
        return (0);
      }
      i++;
    }
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
			if (waitpid(pids[i], last_status, WUNTRACED) == -1)
				return (perror("waitpid"), 1);
			i++;
		}
		pid_index = 0;
	}
	return (0);
}
