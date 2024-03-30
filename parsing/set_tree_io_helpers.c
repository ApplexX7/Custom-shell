/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tree_io_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:37:14 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/29 23:39:20 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*search_for_peer_parenth(t_list *start, int count, int level)
{
	while (start)
	{
		if (is_open_parenth(start))
			level++;
		else if (is_close_parenth(start))
		{
			if (level == 0)
			{
				if (count)
					return (start->next);
				else
					return (NULL);
			}
			else
				level--;
		}
		else if (level == 0 && is_and_or_or(start))
			count++;
		start = start->next;
	}
	return (NULL);
}

// check if there is a combined redirection in the current node
// returns the node of the first redirection
t_list	*check_combined_redirection(t_list *lst)
{
	int	level;
	int	count;

	count = 0;
	lst = skip_spaces(lst);
	if (lst && is_open_parenth(lst))
	{
		level = 0;
		lst = lst->next;
		return (search_for_peer_parenth(lst, count, level));
	}
	return (NULL);
}

int	is_redirect_op(t_list *lst)
{
	if (is_input_redirect(lst))
		return (1);
	else if (is_output_redirect(lst))
		return (1);
	else
		return (0);
}

int	is_input_redirect(t_list *lst)
{
	if (!ft_strncmp(lst->content, "<", 2) && !lst->is_op)
		return (1);
	else if (!ft_strncmp(lst->content, "<<", 3) && !lst->is_op)
		return (1);
	else
		return (0);
}

int	is_output_redirect(t_list *lst)
{
	if (!ft_strncmp(lst->content, ">", 2) && !lst->is_op)
		return (1);
	else if (!ft_strncmp(lst->content, ">>", 3) && !lst->is_op)
		return (1);
	else
		return (0);
}
