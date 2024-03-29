/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 03:14:15 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/29 03:21:32 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

static void	fd_capture(int fd, int fds[OPEN_MAX])
{
	int	i;

	i = 0;
	while (fds[i] != 0 && i < OPEN_MAX)
		i++;
	if (i < OPEN_MAX)
		fds[i] = fd;
}

static int	fd_close_all(int fds[OPEN_MAX])
{
	int	i;

	i = 0;
	while (i < OPEN_MAX)
	{
		if (fds[i] != 1 && fds[i] != 0)
		{
			if (close(fds[i]))
				return (1);
			fds[i] = 0;
		}
		i++;
	}
	return (0);
}

static int	fd_close(int fd, int fds[OPEN_MAX])
{
	int	i;

	i = 0;
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
	return (0);
}

int	manage_fds(int fd, t_fd_action action)
{
	static int	fds[OPEN_MAX] = {0};
	int			i;

	i = 0;
	if (action == CAPTURE)
		fd_capture(fd, fds);
	else if (action == CLOSE_ALL)
	{
		if (fd_close_all(fds))
			return (1);
	}
	else if (action == CLOSE)
	{
		if (fd_close(fd, fds))
			return (1);
	}
	return (0);
}
