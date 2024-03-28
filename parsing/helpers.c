/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:11:48 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/28 18:28:42 by mohilali         ###   ########.fr       */
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
