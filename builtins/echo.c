/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:25:09 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/29 02:35:55 by ayait-el         ###   ########.fr       */
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

/*
int	main(void)
{
  t_list *node;
	t_tree	t;

  node = NULL;
  ft_lstadd_back(&node, ft_lstnew("echo"));
  //ft_lstadd_back(&node, ft_lstnew("-n"));
  ft_lstadd_back(&node, ft_lstnew("hello"));
  ft_lstadd_back(&node, ft_lstnew("world"));
  ft_lstadd_back(&node, ft_lstnew("hello"));
  t = {node, NULL, NULL, 0, 1, NULL, "test"};
  ft_echo (&t);
}
*/
