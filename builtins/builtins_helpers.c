/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 21:50:03 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/28 21:50:10 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	set_fd(int *set, t_tree *root)
{
	int	fd;

	if (root->output_file)
	{
		fd = ft_open(root->output_file, O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
			return (perror("open"), 1);
		return (*set = fd, 0);
	}
	else
		return (*set = root->out_fd, 0);
}

int	ft_putnstr_fd(char *str, int fd, int size)
{
	int	i;

	i = 0;
	while (str[i] && i < size)
	{
		if (write(fd, &str[i], 1) == -1)
			return (perror("write"), 1);
		i++;
	}
	return (0);
}
