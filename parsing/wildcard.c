/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:59:07 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/30 02:28:35 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lst_next_wildcard(t_list *head, t_list **start, t_list **end)
{
	t_list	*s;
	t_list	*e;

	s = head;
	while (head && !is_wildcard(head))
		head = head->next;
	if (!head)
		return (*start = NULL, *end = NULL, 0);
	if (s != head)
	{
		while (s->next != head)
			s = s->next;
		if (s->is_op == 0 && ((char *)s->content)[0] != '$')
			s = head;
	}
	e = head;
	while (e->next && !is_space(e->next))
		e = e->next;
	*start = s;
	*end = e;
	return (0);
}

// add the rest of lst to dest
static int	add_rest_of_lst(t_list *lst, t_list **dest)
{
	while (lst)
	{
		if (add_node(dest, lst))
			return (1);
		lst = lst->next;
	}
	return (0);
}

// allocs: new
int	add_matched_list(t_list **dest, t_list *lst)
{
	t_list	*start;
	t_list	*end;
	t_list	*new;

	lst_next_wildcard(lst, &start, &end);
	while (start && end)
	{
		new = NULL;
		while (lst != start)
		{
			if (add_node(dest, lst))
				return (1);
			lst = lst->next;
		}
		if (get_matched_list(start, end, &new))
			return (ft_lstclear(&new, &free), 1);
		lst = end->next;
		bubblesort(new);
		append_list(new, dest, '\'');
		lst_next_wildcard(lst, &start, &end);
	}
	if (add_rest_of_lst(lst, dest))
		return (1);
	return (0);
}

// allocs: new
// frees lst on sucess
int	expand_wildcard(t_list **lst)
{
	t_list	*new;

	new = NULL;
	if (add_matched_list(&new, *lst))
		return (ft_lstclear(&new, &free), 1);
	ft_lstclear(lst, &free);
	*lst = new;
	return (0);
}
