/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lable_env_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:58:21 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/27 19:58:38 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// else if (lst->is_op == 0 && ((char *) lst->content)[0] == '$')
// lst->is_op = '"';
void	lable_env_args(t_list *lst)
{
	while (lst)
	{
		if (lst->is_op != '\'' && ((char *)lst->content)[0] == '$'
			&& ((char *)lst->content)[1] == '\0')
			lst->is_op = '\'';
		lst = lst->next;
	}
}
