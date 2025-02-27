/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_parenthesis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:59:24 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/29 14:48:46 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_inclosing_parenth(t_list *start, t_list *end, t_list **lst)
{
	lst_remove_node(lst, start);
	lst_remove_node(lst, end);
}

void	set_end(t_list *lst, t_list **end)
{
	int	level;

	level = 0;
	while (lst)
	{
		if (is_open_parenth(lst))
			level++;
		else if (is_close_parenth(lst))
		{
			if (level == 0)
			{
				*end = lst;
				break ;
			}
			else
				level--;
		}
		lst = lst->next;
	}
}

void	remove_parenthesis(t_list **lst)
{
	t_list	*start;
	t_list	*end;
	t_list	*tmp;

	tmp = *lst;
	start = skip_spaces(tmp);
	end = NULL;
	if (start && !is_open_parenth(start))
		return ;
	tmp = start->next;
	set_end(tmp, &end);
	if (end && (end == ft_lstlast(*lst) || (is_space(end->next)
				&& skip_spaces(end->next) == skip_spaces(ft_lstlast(*lst)))))
		remove_inclosing_parenth(start, end, lst);
}
