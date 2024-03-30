/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:25:09 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/30 02:29:14 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

static void	print_echo_list(t_list *lst, int fd, int nflag)
{
	while (lst)
	{
		ft_putstr_fd(lst->content, fd);
		if (lst->next)
			ft_putstr_fd(" ", fd);
		lst = lst->next;
	}
	if (!nflag)
		ft_putstr_fd("\n", fd);
}

int	ft_echo(t_tree *root)
{
	int		nflag;
	int		fd;
	t_list	*lst;

	lst = root->node;
	if (set_fd(&fd, root))
		return (1);
	lst = lst->next;
	nflag = 0;
	if (lst && !ft_strncmp(lst->content, "-n", 3))
	{
		nflag = 1;
		lst = lst->next;
	}
	print_echo_list(lst, fd, nflag);
	if (fd != 1)
		ft_close(fd);
	return (0);
}
