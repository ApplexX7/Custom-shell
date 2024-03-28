/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syn_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:43:18 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/27 23:15:23 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirectionop(t_list *current)
{
	if (!ft_strncmp(current->content, ">", 2) && !current->is_op)
		return (1);
	if (!ft_strncmp(current->content, "<", 2) && !current->is_op)
		return (1);
	if (!ft_strncmp(current->content, "<<", 3) && !current->is_op)
		return (1);
	if (!ft_strncmp(current->content, ">>", 3) && !current->is_op)
		return (1);
	return (0);
}

int	ft_special_operators(t_list *current)
{
	if (!current)
		return (1);
	if (!ft_strncmp(current->content, "&&", 3) && !current->is_op)
		return (1);
	else if (!ft_strncmp(current->content, "||", 3) && !current->is_op)
		return (1);
	else if (!ft_strncmp(current->content, "|", 2) && !current->is_op)
		return (1);
	return (0);
}

int	check_opsyntax(t_list *lst)
{
	t_list	*current;
	int		index;

	current = lst;
	index = 0;
	while (current)
	{
		if (!index && ft_special_operators(current))
			return (1);
		if (ft_redirectionop(current) && !current->next)
			return (1);
		index++;
		current = current->next;
	}
	return (0);
}

int	ft_handle_parentiserror(t_list *lst)
{
	t_list	*current;
	int		index_key;

	current = lst;
	index_key = 0;
	while (current)
	{
		if (index_key && !ft_strncmp(current->content, "(", 2)
			&& !current->is_op)
			return (1);
		if (ft_special_operators(current) || (!ft_strncmp(current->content, "(",
					2) && !current->is_op) || (!ft_strncmp(current->content,
					"<<", 3) && !current->is_op))
			index_key = 0;
		else
			index_key++;
		current = current->next;
	}
	return (0);
}

int	handle_oppositions(t_list *lst)
{
	t_list	*current;

	current = lst;
	while (current)
	{
		if (ft_special_operators(current)
			&& ft_special_operators(current->next))
			return (1);
		else if (ft_redirectionop(current)
			&& ft_special_operators(current->next))
			return (1);
		else if (ft_redirectionop(current) && ft_redirectionop(current->next))
			return (1);
		current = current->next;
	}
	return (0);
}
