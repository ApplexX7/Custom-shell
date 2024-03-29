/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:11:48 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/29 22:11:23 by mohilali         ###   ########.fr       */
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

int	should_join_mask(t_list *start, t_list *end)
{
	int	join;

	join = 0;
	while (start != end)
	{
		if (start->mask)
			join = 1;
		start = start->next;
	}
	return (join);
}

// allocs: tmp, tmp3
int	join_mask(t_list *start, t_list *end, t_list *dest)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = NULL;
	if (should_join_mask(start, end))
	{
		while (start != end)
		{
			if (!start->mask)
			{
				tmp2 = ft_strdup(start->content);
				full_withzero(&tmp2);
			}
			else
			{
				tmp2 = start->mask;
				start->mask = NULL;
			}
			if (!tmp2)
				return (free(tmp), perror("join_mask"), 1);
			tmp3 = tmp;
			tmp = ft_strjoin(tmp, tmp2);
			free(tmp2);
			free(tmp3);
			if (!tmp)
				return (perror("join_mask"), 1);
			start = start->next;
		}
	}
	return (dest->mask = tmp, 0);
}

void	do_nothing(void *arg)
{
	(void)arg;
}

int is_parentis(t_list *node)
{
	if (!ft_strncmp(node->content, "(", 2) && !node->is_op)
		return (1);
	if (!ft_strncmp(node->content, ")", 2) && !node->is_op)
		return (1);
	return (0);
}

void del_parentis(t_list **lst)
{
	t_list *tmp;
  t_list *tmp2;

	tmp = *lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (is_parentis(tmp))
		{
			printf("hello\n");
			lst_remove_node(lst, tmp);
			// tmp = tmp2;
		}
		tmp = tmp2;
	}
}