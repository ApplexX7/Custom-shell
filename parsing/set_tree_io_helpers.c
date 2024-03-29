/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tree_io_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:37:14 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/29 14:15:51 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_redirections(t_tree *node, t_list *start)
{
	t_list	*tmp;
	t_list	*head;

	head = node->node;
	while (start)
	{
		tmp = start->next;
		lst_remove_node(&head, start);
		start = tmp;
	}
	node->node = head;
}

// check if there is a combined redirection in the current node
// returns the node of the first redirection
t_list	*check_combined_redirection(t_list *lst)
{
	int	level;

	lst = skip_spaces(lst);
	if (lst && is_open_parenth(lst))
	{
		level = 0;
		lst = lst->next;
		while (lst)
		{
			if (is_open_parenth(lst))
				level++;
			else if (is_close_parenth(lst))
			{
				if (level == 0)
					return (lst->next);
				else
					level--;
			}
			lst = lst->next;
		}
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
