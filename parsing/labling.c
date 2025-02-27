/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:58:36 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/28 13:42:42 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lable_doublequotes(t_list **current)
{
	(*current)->is_op = 0;
	(*current) = (*current)->next;
	while ((*current))
	{
		if (!ft_strncmp((*current)->content, "\"", 2))
		{
			(*current)->is_op = 0;
			(*current) = (*current)->next;
			return ;
		}
		(*current)->is_op = '"';
		(*current) = (*current)->next;
	}
}

static void	lable_sinlgequotes(t_list **current)
{
	(*current)->is_op = 0;
	(*current) = (*current)->next;
	while ((*current))
	{
		if (!ft_strncmp((*current)->content, "'", 2))
		{
			(*current)->is_op = 0;
			(*current) = (*current)->next;
			return ;
		}
		(*current)->is_op = '\'';
		(*current) = (*current)->next;
	}
}

void	lable_list(t_list *lst)
{
	t_list	*current;

	current = lst;
	while (current)
	{
		if (!ft_strncmp(current->content, "\"", 2))
			lable_doublequotes(&current);
		else if (!ft_strncmp(current->content, "'", 2))
			lable_sinlgequotes(&current);
		else
		{
			current->is_op = 0;
			current = current->next;
		}
	}
}
