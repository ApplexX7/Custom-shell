/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_mask.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:54:19 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/30 00:00:12 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	should_join_mask(t_list *start, t_list *end)
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

// copy the mask or fill with zeros
static int	set_tmp2(char **tmp2, t_list *start)
{
	if (!start->mask)
	{
		*tmp2 = ft_strdup(start->content);
		full_withzero(tmp2);
	}
	else
	{
		*tmp2 = start->mask;
		start->mask = NULL;
	}
	if (!(*tmp2))
		return (perror("set_tmp2"), 1);
	return (0);
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
			if (set_tmp2(&tmp2, start))
				return (free(tmp), 1);
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
