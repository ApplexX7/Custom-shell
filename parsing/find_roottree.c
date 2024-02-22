/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_roottree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:26:06 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/22 18:44:19 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_operator(char *content)
{
	if (!ft_strncmp(content, "&&", 3))
		return (1);
	if (!ft_strncmp(content, "||", 3))
		return (1);
	return (0);
}

void labling_prio(t_list *list)
{
	int count;
	t_list *current;

	count = 0;
	current = list;
	while (current)
	{
		if (find_operator(current->content) && !current->is_op)
			current->prio = count;
		if (!ft_strncmp(current->content, "(", 2) && !current->is_op)
			count++;
		else if (!strncmp(current->content, ")", 2) && !current->is_op)
			count--;
		current	= current->next;
	}
}

t_list *find_roottree(t_list *list)
{
	t_list *current;
	t_list * tmp;
	int count;
	int pri_count;

	labling_prio(list);
	current = list;
	tmp = NULL;
	count = 0;
	pri_count = 0;
	while (current)
	{
		if (find_operator(current->content) && !current->is_op)
		{
			if (count == 0)
				pri_count = current->prio;
			if (find_operator(current->content) && pri_count >= current->prio)
			{
				tmp = current;
				pri_count = current->prio;
			}
			count++;
		}
		current = current->next;
	}
	return (tmp);
}
