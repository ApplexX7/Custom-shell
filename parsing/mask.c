/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:20:58 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/15 01:56:56 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void full_withzero(char **s)
{
	int i;
	char *str;

	str = *s;
	i = 0;
	while (str[i])
	{
		str[i] = '0';
		i++;
	}
}
void full_withone(char **s)
{
	int i;
	char *str;

	str = *s;
	i = 0;
	while (str[i])
	{
		str[i] = '1';
		i++;
	}
}

int there_is_expand(t_list *start, t_list *end)
{
	t_list * current_start;

	current_start = start;
	while (current_start && current_start <= end)
	{
		if (ft_strchr(current_start->content, '$'))
			return (0);
		current_start = current_start->next;
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
	while (start && start <= end)
	{
		tmp = ft_strdup(start->content);
		if (!tmp)
			return (1);
		// printf("%s\n", start->content);
		if (ft_strchr(start->content, '$') && (!start->is_op || start->is_op == '\"'))
		{	
			full_withone(&tmp);
		}
		else
			full_withzero(&tmp);
		tmp2 = new;
		new = ft_strjoin(new, tmp);
		free(tmp2);
		free(tmp);
		if (!new)
			return (1);
		printf("%s\n", new);
		start = start->next;
	}
	*dest = new;
	return (0);
}
