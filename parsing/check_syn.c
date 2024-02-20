/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:58:54 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/20 18:59:11 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void lst_remove_node(t_list **lst, t_list *node)
{
  t_list *tmp;

  tmp = *lst;
  if (tmp == node)
  {
    *lst = node->next;
    ft_lstdelone(node, &free);
  }
  while (tmp->next)
  {
    if (tmp->next == node)
    {
      tmp->next = node->next;
      ft_lstdelone(node, &free);
      return ;
    }
    tmp = tmp->next;
  }
}

int is_space(t_list *node)
{
  if (!strncmp(node->content, " ", 2) && !node->is_op)
    return (1);
  else
    return (0);
}

void del_spaces(t_list **lst)
{
  t_list *tmp;

  tmp = *lst;
  while (tmp)
  {
    if (is_space(tmp))
      lst_remove_node(lst, tmp);
    tmp = tmp->next;
  }
}

t_list *skip_spaces(t_list *start)
{
  while (start && is_space(start))
    start = start->next;
  return (start);
}

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
	if (count_parentisright != count_parentislift || (count_quotes % 2 != 0 && count_quotes != 0))
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

void	check_parentis(t_list *list)
{
	int count;
	
	count = 0;
	while (list)
	{
		if (!ft_strncmp(list->content, "("))
	}
}

void check_syn(t_list *list)
{
	t_list *copy;

	copy = copy_lst(list);
	del_spaces(&copy);
	if (valid_struct(copy))
	{
		printf("syntax error: unclosed charcters\n");
		ft_lstclear(&copy, &free);
		ft_lstclear(&list, &free);
		return ;
	}
	if (valid_syntax(copy))
	{
		printf("syntax error: near unexpected tokens '%s' \n", (char *)copy->content);
		ft_lstclear(&copy, &free);
		ft_lstclear(&list, &free);
		return ;
	}
	if (check_operatoresorder(copy))
	{
		printf("sybtax error: near unexpected token '%s'\n", (char *)copy->content);
		ft_lstclear(&copy, &free);
		ft_lstclear(&list, &free);
		return ;
	}
	if (check_parentis(copy))
		;
}
