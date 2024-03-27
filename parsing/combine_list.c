/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:41:07 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/27 18:45:09 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_nonliterals(t_list *start, t_list **head, t_list **tmp)
{
	while (start && !start->is_op && ((char *)start->content)[0] != '$')
	{
		if (add_node(head, start) || masking(start, start->next,
				ft_lstlast(*head)))
			return (1);
		start = start->next;
	}
	*tmp = start;
	return (0);
}

t_list	*skip_literals(t_list *start)
{
	while (start && (start->is_op || ((char *)start->content)[0] == '$'))
		start = start->next;
	return (start);
}

int	is_breaking_token(t_list *node)
{
	if (!ft_strncmp(node->content, "<<", 3) && !node->is_op)
		return (1);
	else if (!ft_strncmp(node->content, ">>", 3) && !node->is_op)
		return (1);
	else if (!ft_strncmp(node->content, "|", 2) && !node->is_op)
		return (1);
	else if (!ft_strncmp(node->content, ">", 2) && !node->is_op)
		return (1);
	else if (!ft_strncmp(node->content, "<", 2) && !node->is_op)
		return (1);
	else if (!ft_strncmp(node->content, "||", 3) && !node->is_op)
		return (1);
	else if (!ft_strncmp(node->content, "&&", 3) && !node->is_op)
		return (1);
	else if (!strncmp(node->content, " ", 2) && !node->is_op)
		return (1);
	else if (ft_strchr(node->content, '*') && !node->is_op)
		return (1);
	return (0);
}

// allocs: new
// frees lst on success
int	combine_lits_with_nonlists(t_list **lst)
{
	t_list	*new;
	t_list	*tmp;
	t_list	*start;

	new = NULL;
	tmp = *lst;
	while (tmp)
	{
		if ((!is_breaking_token(tmp) && !is_literal(tmp)
				&& is_literal(tmp->next)) || is_literal(tmp))
		{
			start = tmp;
			while (tmp && !is_breaking_token(tmp))
				tmp = tmp->next;
			if (join_and_add(&new, start, tmp))
				return (ft_lstclear(&new, &free), 1);
		}
		else
		{
			if (add_node(&new, tmp))
				return (ft_lstclear(&new, &free), 1);
			tmp = tmp->next;
		}
	}
	return (ft_lstclear(lst, &free), *lst = new, 0);
}

// allocs: new
// frees lst on success
// it deletes the quotes and combine the literals
int	combine_list(t_list **lst)
{
	t_list	*tmp;
	t_list	*new;
	t_list	*start;

	del_useless_tokens(lst);
	tmp = *lst;
	new = NULL;
	if (skip_nonliterals(tmp, &new, &tmp))
		return (ft_lstclear(&new, &free), 1);
	start = tmp;
	while (tmp)
	{
		tmp = skip_literals(tmp);
		if (join_and_add(&new, start, tmp) || masking(start, tmp,
				ft_lstlast(new)))
			return (ft_lstclear(&new, &free), 1);
		if (skip_nonliterals(tmp, &new, &tmp))
			return (ft_lstclear(&new, &free), 1);
		start = tmp;
	}
	if (combine_lits_with_nonlists(&new))
		return (ft_lstclear(&new, &free), 1);
	ft_lstclear(lst, &free);
	*lst = new;
	return (0);
}

/*
int	main(void)
{
	t_list	*lst;
	t_list	*first;
	t_list	*mid;
	t_list	*end;

  lst = NULL;
  first = ft_lstnew(ft_strdup("first"));
  mid = ft_lstnew(ft_strdup("mid"));
  end = ft_lstnew(ft_strdup("end"));
  ft_lstadd_back(&lst, first);
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, mid);
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, end);
  lst_remove_node(&lst, first);
  lst_remove_node(&lst, mid);
  lst_remove_node(&lst, end);
  printf("%s\n", join_list(lst));
}
*/

/*
int	main(void)
{
	t_list	*lst;
	t_list	*first;
	t_list	*mid;
	t_list	*end;

  lst = NULL;
  first = ft_lstnew(ft_strdup("first"));
  mid = ft_lstnew(ft_strdup("mid"));
  end = ft_lstnew(ft_strdup("end"));
  ft_lstadd_back(&lst, first);
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, mid);
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, ft_lstnew("--"));
  ft_lstadd_back(&lst, end);
  lst_remove_node(&lst, first);
  lst_remove_node(&lst, mid);
  lst_remove_node(&lst, end);
  print_ouput(lst);
}
*/
