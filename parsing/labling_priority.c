/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labling_priority.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:26:06 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/23 12:17:39 by mohilali         ###   ########.fr       */
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
		else if (!ft_strncmp(current->content, "|", 2) && !current->is_op)
			current->prio = count + 1;
		else
			current->prio = count;
		if (!ft_strncmp(current->content, "(", 2) && !current->is_op)
			count++;
		else if (!strncmp(current->content, ")", 2) && !current->is_op)
			count--;
		current	= current->next;
	}
}



t_list *find_roottree(t_list **list)
{
	t_list *current;
	t_list * tmp;
	t_list *tmp2;
	t_list *tmp3;
	int count;
	int pri_count;

	current = *list;
	tmp = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	count = 0;
	pri_count = 0;
	while (current)
	{
		if ((find_operator(current->content) || !ft_strncmp(current->content, "|", 2)) && !current->is_op)
		{
			if (count == 0)
				pri_count = current->prio;
			if ((find_operator(current->content) || !ft_strncmp(current->content, "|", 2)) && pri_count >= current->prio)
			{
				tmp3 = tmp2;
				tmp = current;
				pri_count = current->prio;
			}
			count++;
		}
		tmp2 = current;
		current = current->next;
	}
	if (tmp3)
		tmp3->next = NULL;
	return (tmp);
}
