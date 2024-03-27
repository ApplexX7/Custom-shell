/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:58:54 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/27 18:05:12 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error_handling(t_list *copy)
{
	ft_lstclear(&copy, &free);
	printf("bash: syntax error in tokens\n");
}

int	valid_parentis(t_list *lst)
{
	t_list	*current;
	int		index;

	current = lst;
	index = 0;
	while (current)
	{
		if (!ft_strncmp(current->content, "(", 2) && !current->is_op)
			index++;
		else if (index && !ft_strncmp(current->content, ")", 2)
			&& !current->is_op)
			return (1);
		else if (ft_special_operators(current) || ft_redirectionop(current))
			index++;
		else if (!ft_special_operators(current) && !ft_redirectionop(current))
			index = 0;
		else if (index > 1 && !ft_redirectionop(current))
			return (1);
		current = current->next;
	}
	return (0);
}

int	valid_syntax(t_list *lst)
{
	if (check_opsyntax(lst))
		return (1);
	if (ft_handle_parentiserror(lst))
		return (1);
	if (handle_oppositions(lst))
		return (1);
	if (valid_parentis(lst))
		return (1);
	return (0);
}

int	closed_qpsayntax(t_list *lst)
{
	t_list	*current;
	int		count_leftparentis;
	int		count_rightparentis;
	int		count_double_qoutes;
	int		count_single_quots;

	current = lst;
	count_leftparentis = 0;
	count_rightparentis = 0;
	count_double_qoutes = 0;
	count_single_quots = 0;
	while (current)
	{
		if (!ft_strncmp(current->content, "(", 2) && !current->is_op)
			count_leftparentis++;
		else if (!ft_strncmp(current->content, ")", 2) && !current->is_op)
			count_rightparentis++;
		else if (!ft_strncmp(current->content, "\"", 2) && !current->is_op)
			count_double_qoutes++;
		else if (!ft_strncmp(current->content, "'", 2) && !current->is_op)
			count_single_quots++;
		current = current->next;
	}
	if ((count_leftparentis != count_rightparentis) || (count_single_quots
			% 2 != 0) || (count_double_qoutes % 2 != 0))
		return (1);
	return (0);
}

int	check_syntax(t_list *lst, int *status_code)
{
	t_list	*current;

	current = copy_lst(lst);
	del_spaces(&current);
	if (closed_qpsayntax(current))
	{
		syntax_error_handling(current);
		return (status_code_of_syntax_error(status_code), 1);
	}
	if (valid_syntax(current))
	{
		syntax_error_handling(current);
		return (status_code_of_syntax_error(status_code), 1);
	}
	ft_lstclear(&current, &free);
	return (0);
}
