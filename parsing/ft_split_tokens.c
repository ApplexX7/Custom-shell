/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:31:01 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/23 17:15:08 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void free_node(t_list **head)
{
	t_list *current;

	current = *head;
	while (current)
	{
		free(current->content);
		current = current->next;
	}
	free(head);
}


int ft_issspace(int c)
{
	if (c == '\n' || c == '\v' || c == '\f'
		|| c == '\t' || c == '\r')
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
	if (c == '|' || c == '>' || c == '<' || c == '&' || c == '"'
		|| c == '\'' || c == '(' || c == ')' || c == ' ')
		return 1;
	return 0;
}

int add_tolist(char *av, t_list **head, int index, int start)
{
	int end;
	t_list *new;
  char *content;

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

int	ft_normalcharacters(char *av, t_list **head, int *index)
{
	int	start;
	int	count;
	
	start = *index;
	count = 0;
	while(av[(*index)] && !ft_isspecial(av[(*index)]) && !ft_issspace(av[(*index)]))
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
			break;
		}
		(*index)++;
	}
	if (add_tolist(av, head, *index, start))
		return (1);
	return (0);
}

int	ft_tokencharcters(char *av, t_list **head, int *index)
{
	int start;
	
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
	if (add_tolist(av,  head, *index, start))
		return (1);
	return (0);
}

t_list *split_tokens(char *av)
{
	int i;
	t_list *cmd;

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
