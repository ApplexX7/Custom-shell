/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unqoutes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:31:01 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/15 12:16:32 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_ouput(t_cmd *node)
{
	while (node != NULL)
	{
		printf("%s\n", node->data);
		node = node->next;
	}	
}

void	ft_lstadd_back1(t_cmd **lst, t_cmd *new)
{
	t_cmd	*current;

	if (!lst || ! new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new;
	}
}

t_cmd	*ft_lstnew1(void *content)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->data = content;
	node->next = NULL;
	return (node);
}

int ft_issspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\t' || c == '\r')
		return (1);
	return (0);
	
}


int	ft_isspecial(int c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&')
		return 1;
	return 0;
}

void hanlde_unquatoes(char *av)
{
	int i;
	int start;
	int end;
	t_cmd *cmd;
	t_cmd *new;

	cmd = NULL;

	start = 0;
	i = 0;
	while (av[i])
	{
		while (ft_issspace(av[i]) && av[i])
			i++;
		start = i;
		while(av[i] && !ft_isspecial(av[i]) && !ft_issspace(av[i]))
			i++;
		if (i > 0)
		{	
			end = i;
			new = ft_lstnew1(ft_substr(av, start, end - start));
			if (new->data[0] != '\0')
				ft_lstadd_back1(&cmd, new);
			start = i;
		}
		while (ft_issspace(av[i]) && av[i])
			i++;
		start = i;
		while (av[i] && (ft_isspecial(av[i]) && !ft_issspace(av[i])))
		{
			if (av[i] == av[i + 1])
			{
				i += 1;
			}
			else
			{
				i++;
				break;
			}
		}
		if (i > 0)
		{
			end = i;
			new = ft_lstnew1(ft_substr(av, start, end - start));
			if (new->data[0] != '\0')
				ft_lstadd_back1(&cmd, new);
		}
	}
	print_ouput(cmd);
}
