/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lable_env_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:58:21 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/28 00:26:28 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	next_is_quote(t_list *next)
{
	if (next && !next->is_op && next->next && next->next->is_op)
	{
		if (!ft_strncmp(next->content, "\"", 2))
			return (1);
		else if (!ft_strncmp(next->content, "'", 2))
			return (1);
	}
	return (0);
}

// else if (lst->is_op == 0 && ((char *) lst->content)[0] == '$')
// lst->is_op = '"';
void	lable_env_args(t_list *lst)
{
	while (lst)
	{
		if (lst->is_op != '\'' && ((char *)lst->content)[0] == '$'
			&& ((char *)lst->content)[1] == '\0' && !next_is_quote(lst->next))
			lst->is_op = '\'';
		lst = lst->next;
	}
}
