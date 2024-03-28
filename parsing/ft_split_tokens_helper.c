/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokens_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:23:33 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/27 17:27:02 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tokencharcters(char *av, t_list **head, int *index)
{
	int	start;

	start = *index;
	while (av[(*index)] && (ft_isspecial(av[(*index)])))
	{
		if (ft_isnotdouble(av[(*index)]) && av[(*index)] == av[(*index) + 1])
		{
			(*index) += 2;
			break ;
		}
		else
		{
			(*index)++;
			break ;
		}
	}
	if (add_tolist(av, head, *index, start))
		return (1);
	return (0);
}

int	ft_normalcharacters(char *av, t_list **head, int *index)
{
	int	start;
	int	count;

	start = *index;
	count = 0;
	while (av[(*index)] && !ft_isspecial(av[(*index)])
		&& !ft_issspace(av[(*index)]))
	{
		if (av[(*index)] == '$' && av[(*index + 1)] == '?')
		{
			count++;
			(*index)++;
		}
		if (av[(*index) + 1] == '$')
			count++;
		if (count >= 1)
		{
			(*index)++;
			break ;
		}
		(*index)++;
	}
	if (add_tolist(av, head, *index, start))
		return (1);
	return (0);
}

int	add_tolist(char *av, t_list **head, int index, int start)
{
	int		end;
	t_list	*new;
	char	*content;

	if ((index) > 0)
	{
		end = (index);
		content = ft_substr(av, start, end - start);
		if (!content)
			return (1);
		new = ft_lstnew(content);
		if (!new)
			return (free(content), 1);
		if (((char *)new->content)[0] != '\0')
			ft_lstadd_back(head, new);
		else
		{
			free(new->content);
			free(new);
		}
	}
	return (0);
}
