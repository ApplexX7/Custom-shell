/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:11:48 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/30 00:00:43 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_wildcard(t_list *node)
{
	if (ft_strchr(node->content, '*') && !node->is_op)
		return (1);
	else
		return (0);
}

void	do_nothing(void *arg)
{
	(void)arg;
}

int	is_parentis(t_list *node)
{
	if (!ft_strncmp(node->content, "(", 2) && !node->is_op)
		return (1);
	if (!ft_strncmp(node->content, ")", 2) && !node->is_op)
		return (1);
	return (0);
}

void	del_parentis(t_list **lst)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (is_parentis(tmp))
		{
			lst_remove_node(lst, tmp);
			// tmp = tmp2;
		}
		tmp = tmp2;
	}
}
