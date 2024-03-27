/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:31:01 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/27 17:24:59 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_issspace(int c)
{
	if (c == '\n' || c == '\v' || c == '\f' || c == '\t' || c == '\r')
		return (1);
	return (0);
}

int	ft_isnotdouble(int c)
{
	if (c != '"' && c != '\'' && c != '(' && c != ')' && c != ' ')
		return (1);
	return (0);
}

int	ft_isspecial(int c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&' || c == '"' || c == '\''
		|| c == '(' || c == ')' || c == ' ')
		return (1);
	return (0);
}

t_list	*split_tokens(char *av)
{
	int		i;
	t_list	*cmd;

	cmd = NULL;
	i = 0;
	while (av[i])
	{
		while (av[i] && ft_issspace(av[i]) && av[i] != ' ')
			i++;
		if (ft_normalcharacters(av, &cmd, &i))
		{
			ft_lstclear(&cmd, &free);
			return (NULL);
		}
		while (av[i] && ft_issspace(av[i]))
			i++;
		if (ft_tokencharcters(av, &cmd, &i))
		{
			ft_lstclear(&cmd, &free);
			return (NULL);
		}
	}
	return (cmd);
}
