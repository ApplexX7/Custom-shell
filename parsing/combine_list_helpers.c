/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_list_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:45:45 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/27 18:45:47 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// spaces are useful but after will be useless
int	is_useless_token(t_list *node)
{
	if (!strncmp(node->content, "\'", 2) && !node->is_op)
		return (1);
	else if (!strncmp(node->content, "\"", 2) && !node->is_op)
		return (1);
	return (0);
}

// return 1 if consecutive quotes found
int	handle_consecutive_quotes(t_list *node)
{
	if (!node->next)
		return (0);
	else if (!strncmp(node->content, "'", 2) && !node->is_op
		&& !strncmp(node->next->content, "'", 2) && !node->next->is_op)
		return (1);
	else if (!strncmp(node->content, "\"", 2) && !node->is_op
		&& !strncmp(node->next->content, "\"", 2) && !node->next->is_op)
		return (1);
	else
		return (0);
}

// deletes useless tokens defined by is_useless_token
void	del_useless_tokens(t_list **lst)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (handle_consecutive_quotes(tmp))
		{
			tmp->is_op = ((char *)tmp->content)[0];
			((char *)tmp->content)[0] = '\0';
		}
		else if (is_useless_token(tmp))
			lst_remove_node(lst, tmp);
		tmp = tmp2;
	}
}

// return 1 if node is literal, note: $ node also considered literals
int	is_literal(t_list *node)
{
	if (node && (node->is_op || ((char *)node->content)[0] == '$'))
		return (1);
	else
		return (0);
}
