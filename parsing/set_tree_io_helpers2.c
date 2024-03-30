/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tree_io_helpers2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:41:40 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/29 23:41:44 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_redirections(t_tree *node, t_list *start)
{
	t_list	*tmp;
	t_list	*head;

	head = node->node;
	while (start)
	{
		tmp = start->next;
		lst_remove_node(&head, start);
		start = tmp;
	}
	node->node = head;
}

int	is_and_or_or(t_list *node)
{
	if (!ft_strncmp(node->content, "&&", 3) && !node->is_op)
		return (1);
	else if (!ft_strncmp(node->content, "||", 3) && !node->is_op)
		return (1);
	else
		return (0);
}
