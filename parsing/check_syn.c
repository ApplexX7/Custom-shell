/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:58:54 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/21 14:48:14 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int checkttokenspace(t_list *list)
{
	if (!list)
		return (1);
	if ((!ft_strncmp(list->content, ">>", 3) || !ft_strncmp(list->content, "<<", 3)) && !list->is_op)
		return (1);
	if ((!ft_strncmp(list->content, "||", 3) || !ft_strncmp(list->content, "&&", 3)) && !list->is_op)
		return (1);
	if ((!ft_strncmp(list->content, "<", 2) || !ft_strncmp(list->content, ">", 2)) && !list->is_op)
		return (1);
	if (!ft_strncmp(list->content, "|", 2) && !list->is_op)
		return (1);
	return (0);
}

/*
	function that check if 
	the "(,), ', ", " unclosed 
	or are node the same;
	TODO: move "(,)" in the 
	Mandatory part
*/

int	valid_struct(t_list *list)
{
	t_list *current;
	int		count_parentislift;
	int		count_parentisright;
	int		count_quotes;

	count_parentislift = 0;
	count_parentisright = 0;
	count_quotes = 0;
	current = list;
	while (current)
	{
		if (!ft_strncmp(current->content, "(", 2) && !current->is_op)
			count_parentislift++;
		if (!ft_strncmp(current->content, "\"", 2) && !current->is_op)
			count_quotes++;
		if (!ft_strncmp(current->content, "'", 2) && !current->is_op)
			count_quotes++;
		if (!ft_strncmp(current->content, ")", 2) && !current->is_op)
			count_parentisright++;
		current = current->next;
	}
	if (count_parentisright != count_parentislift
		|| (count_quotes % 2 != 0 && count_quotes != 0))
			return (1);
	return (0);
}

int ensurevalid_syntax(t_list *list)
{
	if (checkttokenspace(list) && checkttokenspace(list->next))
	{
		if (list->next && !ft_strncmp(list->content, ">", 2)
			&& !ft_strncmp(list->next->content, "|", 2))
			return (0);
		else if (list->next && !ft_strncmp(list->content, "|", 2)
			&& !ft_strncmp(list->next->content, "<", 2))
			return (0);
		else if (list->next && !ft_strncmp(list->content, "|", 2)
			&& !ft_strncmp(list->next->content, "<<", 3))
			return (0);
		else if (list->next && !ft_strncmp(list->content, "|", 2)
			&& !ft_strncmp(list->next->content, ">>", 3))
			return (0);
		return (1);
	}
	return (0);
}

int valid_syntax(t_list *list)
{
	t_list *current;
	int		count;
	
	count = 0;
	current = list;
	while(current)
	{
		if (ensurevalid_syntax(current))
			return (1);
		current = current->next;
	}
	return (0);
}

int	check_operatoresorder(t_list *list)
{
	int count;

	count = 0;
	while (list)
	{
		if (ensurevalid_syntax(list))
		{
			if (ensurevalid_syntax(list))
				count++;
		}
		list = list->next;
	}
	if (count)
		return (1);
	return (0);
}


t_list *copy_lst(t_list *lst)
{
  char *content;
  t_list *new;
  t_list *node;

  new = NULL;
  while (lst)
  {
    content = ft_strdup(lst->content);
    if (!content)
      return (ft_lstclear(&new, &free), NULL);
    node = ft_lstnew(content);
    if (!node)
      return (ft_lstclear(&new, &free), free(content), NULL);
	node->is_op = lst->is_op;
    ft_lstadd_back(&new, node);
    lst = lst->next;
  }
  return (new);
}

int tokenparencheck(t_list *list)
{

	while (list)
	{
		if (checkttokenspace(list))
		{
			list = list->next;
			if (!list)
				return (1);
			if (!ft_strncmp(list->content, ")", 2))
				return (1);
		}
		else if (valid_syntax(list))
			return (1);
		list = list->next;
	}
	return (0);
}

int	check_parentis(t_list *list)
{
	while (list)
	{
		if (!ft_strncmp(list->content, "(", 2))
		{
			list = list->next;
			if (!list)
				return (1);
			if (!ft_strncmp(list->content, ")", 2))
				return (1);
		}
		if (tokenparencheck(list))
			return (1);
		list = list->next;
	}
	return (0);
}

void	syntax_error_handling(t_list *list, t_list *copy)
{
	ft_lstclear(&copy, &free);
	ft_lstclear(&list, &free);
	printf("bash: syntax error in tokens\n");
}

int check_syn(t_list *list)
{
	t_list *copy;

	copy = copy_lst(list);
	del_spaces(&copy);
	if (valid_struct(copy))
	{
		syntax_error_handling(list, copy);
		return (1);
	}
	if (valid_syntax(copy))
	{
		syntax_error_handling(list, copy);
		return (1);
	}
	if (check_operatoresorder(copy))
	{
		syntax_error_handling(list, copy);
		return (1);
	}
	if (check_parentis(copy))
	{
		syntax_error_handling(list, copy);
		return (1);
	}
	return (0);
}
