/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unqoutes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:31:01 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/15 18:23:54 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_ouput(t_list *node)
{
	while (node != NULL)
	{
		printf("%s\n", (char *)node->content);
		node = node->next;
	}	
}


int ft_issspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\t' || c == '\r')
		return (1);
	return (0);
	
}

int	ft_isnotdouble(int c)
{
	if (c != '"' && c != '\'' && c != '(' && c != ')')
		return (1);
	return (0);
}

int	ft_isspecial(int c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&' || c == '"'
		|| c == '\'' || c == '(' || c == ')')
		return 1;
	return 0;
}

void	ft_normalcharacters(char *av, t_list **head, int *index)
{
	int	start;
	t_list *new;
	int end;
	
	start = *index;
	while(av[(*index)] && !ft_isspecial(av[(*index)]) && !ft_issspace(av[(*index)]))
		(*index)++;
	if ((*index) > 0)
	{	
		end = (*index);
		new = ft_lstnew(ft_substr(av, start, end - start));
		if (((char *)new->content)[0] != '\0')
			ft_lstadd_back(head, new);
	}
}

void	ft_tokencharcters(char *av, t_list **head, int *index)
{
	int start;
	t_list *new;
	int end;
	
	start = *index;
	while (av[(*index)] && (ft_isspecial(av[(*index)])))
	{
		if (ft_isnotdouble(av[(*index)]) && av[(*index)] == av[(*index) + 1])
		{
			(*index) += 2;
			break;
		}
		else
		{
			(*index)++;
			break;
		}
	}
	if ((*index) > 0)
	{
		end = (*index);
		new = ft_lstnew(ft_substr(av, start, end - start));
		if (((char *)new->content)[0] != '\0')
			ft_lstadd_back(head, new);
	}
}

void split_tokens(char *av)
{
	int i;
	t_list *cmd;

	cmd = NULL;

	i = 0;
	while (av[i])
	{
		while (ft_issspace(av[i]) && av[i])
			i++;
		ft_normalcharacters(av, &cmd, &i);
		while (ft_issspace(av[i]) && av[i])
			i++;
		ft_tokencharcters(av, &cmd, &i);
	}
	print_ouput(cmd);
}
