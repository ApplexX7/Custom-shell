/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:20:58 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/15 00:10:12 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void full_withzero(char **str)
{
	int i;

	i = 0;
	while (*str[i])
	{
		*str[i] = '0';
		i++;
	}
}
void full_withone(char **str)
{
	int i;

	i = 0;
	while (*str[i])
	{
		*str[i] = '1';
		i++;
	}
}

int there_is_expand(t_list *start, t_list *end)
{
	while (start && start != end)
	{
		if (!ft_strchr(start->content, "$"))
			return (0);
		start = start->next;
	}
	return (1);
}

int masking(t_list *start, t_list *end, char **dest)
{
	char *new;
	char *tmp2;
	char *tmp;

	new = *dest;

	if (there_is_expand(start, end))
	{
		*dest = NULL;
		return (0);
	}
	while (start && start != end)
	{
		tmp = ft_strdup(start->content);
		if (!tmp)
			return (1);
		if (ft_strchr(start->content, "$") && (!start->is_op || start->is_op == '\"'))
			full_withone(&tmp);
		else
			full_withzero(&tmp);
		tmp2 = new;
		new = ft_strjoin(new, tmp);
		free(tmp2);
		free(tmp);
		if (!new)
			return (1);
		start = start->next;
	}
	return (0);
}
