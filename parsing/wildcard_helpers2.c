/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_helpers2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:13:02 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/27 23:16:30 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// allocs: new
// it frees lst on sucess
// it also set the open_end bit and open_start bit
int	split_by_star(t_list **lst)
{
	t_list	*new;
	t_list	*tmp;

	tmp = *lst;
	new = NULL;
	if (!is_wildcard(tmp))
	{
		if (new_and_add(&new, tmp->content, tmp->is_op))
			return (ft_lstclear(&new, &free), 1);
		tmp = tmp->next;
	}
	if (split_and_add(tmp, &new))
		return (ft_lstclear(&new, &free), 1);
	if (tmp->next && !is_wildcard(tmp->next))
	{
		if (new_and_add(&new, tmp->next->content, tmp->next->is_op))
			return (ft_lstclear(&new, &free), 1);
	}
	return (ft_lstclear(lst, &free), *lst = new, 0);
}

void	set_ends(int *open_end, int *open_start, t_list *lst)
{
	t_list	*last;

	last = ft_lstlast(lst);
	*open_end = (((char *)last->content)[ft_strlen(last->content) - 1] == '*'
			&& !last->is_op);
	*open_start = (((char *)lst->content)[0] == '*' && !lst->is_op);
}

int	add_if_nomatch(t_list **dest, t_list *start, t_list *end, int matched)
{
	if (!matched)
	{
		if (join_and_add(dest, start, end->next))
			return (1);
	}
	return (0);
}

// allocs: files
int	add_if_matched(t_list **dest, t_list *portion, int ends[2], int *matched)
{
	t_list	*files;
	int		open_end;
	int		open_start;
	t_list	*tmp;

	open_end = ends[0];
	open_start = ends[1];
	files = get_current_files();
	if (!files)
		return (1);
	tmp = files;
	while (tmp)
	{
		if (is_matched(tmp->content, portion, open_end, open_start))
		{
			*matched = 1;
			if (new_and_add(dest, tmp->content, '\''))
				return (ft_lstclear(&files, &free), 1);
		}
		tmp = tmp->next;
	}
	ft_lstclear(&files, &free);
	return (0);
}

// allocs: arr
int	split_and_add(t_list *tmp, t_list **dest)
{
	char	**arr;
	int		i;

	arr = ft_split(tmp->content, '*');
	if (!arr)
		return (1);
	i = 0;
	while (arr[i])
	{
		if (new_and_add(dest, arr[i], 0))
			return (free_2d_arr((void **)arr), 1);
		i++;
	}
	free_2d_arr((void **)arr);
	return (0);
}
