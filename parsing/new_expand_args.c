/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_expand_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:36:25 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/30 02:27:56 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// allocs: new;
int	combine_expand_list(t_list **lst)
{
	t_list	*tmp;
	t_list	*before;
	t_list	*after;

	tmp = *lst;
	before = NULL;
	while (tmp)
	{
		after = tmp->next;
		if (!tmp->is_op)
		{
			if (before && before->is_op)
			{
				if (join_before(before, lst, tmp))
					return (1);
				tmp = before;
			}
			if (after && after->is_op && join_after(after, lst, tmp))
				return (1);
		}
		before = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	get_arg_values_and_expand(char *content, t_list **dest)
{
	char	**arr;
	char	*value;

	arr = ft_split(content, '$');
	if (!arr)
		return (perror("get_arg_values_and_expand"), 1);
	if (join_values(arr, &value))
		return (perror("get_arg_values_and_expand"), 1);
	if (value && new_and_add(dest, value, '"'))
		return (free(value), free_2d_arr((void **)arr), 1);
	free(value);
	free_2d_arr((void **)arr);
	return (0);
}

// allocs: new
int	expand(t_list **lst)
{
	t_list	*new;
	t_list	*tmp;

	new = NULL;
	tmp = *lst;
	while (tmp)
	{
		if (!tmp->is_op)
		{
			if (get_arg_values_and_expand(tmp->content, &new))
				return (ft_lstclear(&new, &free), 1);
		}
		else
		{
			if (add_node(&new, tmp))
				return (ft_lstclear(&new, &free), perror("malloc"), 1);
		}
		tmp = tmp->next;
	}
	ft_lstclear(lst, &free);
	*lst = new;
	return (0);
}

// allocs: splited, value
int	expand_and_add(t_list *node, t_list **dest)
{
	t_list	*splited;
	char	*value;

	splited = get_splited_list(node->content, node->mask);
	if (!splited)
		return (1);
	if (expand(&splited))
		return (ft_lstclear(&splited, &free), 1);
	if (ft_lstjoin(splited, &value))
		return (ft_lstclear(&splited, &free), 1);
	ft_lstclear(&splited, &free);
	if (handle_empty_string_case(&value, node))
		return (free(value), 1);
	if (lst_add_env_arg(value, dest))
		return (free(value), 1);
	return (free(value), 0);
}

// allocs: new
// frees lst on success
int	expand_args(t_list **lst)
{
	t_list	*tmp;
	t_list	*new;

	tmp = *lst;
	new = NULL;
	while (tmp)
	{
		if (tmp->mask)
		{
			if (expand_and_add(tmp, &new))
				return (ft_lstclear(&new, &free), 1);
		}
		else
		{
			if (add_node(&new, tmp))
				return (ft_lstclear(&new, &free), perror("malloc"), 1);
		}
		tmp = tmp->next;
	}
	ft_lstclear(lst, &free);
	*lst = new;
	return (0);
}
