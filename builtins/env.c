/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:20:24 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/28 18:23:16 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	ft_env(t_tree *node, t_list **local_lst)
{
	static t_list	**lst = NULL;
	t_list			*tmp;
	int				fd;

	if (local_lst)
		lst = local_lst;
	else
	{
		if (set_fd(&fd, node))
			return (1);
		tmp = *lst;
		while (tmp)
		{
			if (ft_strchr(tmp->content, '='))
			{
				ft_putstr_fd(tmp->content, fd);
				ft_putstr_fd("\n", fd);
			}
			tmp = tmp->next;
		}
		if (fd != 1 && ft_close(fd) == -1)
			return (perror("close"), 1);
	}
	return (0);
}
