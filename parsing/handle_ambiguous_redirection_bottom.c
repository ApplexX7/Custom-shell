/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ambiguous_redirection_bottom.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:45:09 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/29 23:50:55 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_breaking_token2(t_list *node)
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
	return (0);
}

static void	remove_extra_nodes(t_list *file, t_list *file_end)
{
	t_list	*tmp;
	t_list	*tmp2;

	if (file != file_end)
	{
		tmp = file->next;
		while (tmp != file_end)
		{
			tmp2 = tmp->next;
			lst_remove_node(&file, tmp);
			tmp = tmp2;
		}
		lst_remove_node(&file, tmp);
	}
}

int	handle_ambiguous_redirection_bottom(t_list *file)
{
	t_list	*tmp;
	t_list	*new;
	t_list	*file_end;

	file_end = file;
	while (file_end->next && !is_breaking_token2(file_end->next))
		file_end = file_end->next;
	tmp = file_end->next;
	file_end->next = NULL;
	new = copy_lst(file);
	file_end->next = tmp;
	if (!new)
		return (perror("malloc"), 1);
	if (expand_args(&new))
		return (ft_lstclear(&new, &free), 1);
	if (expand_wildcard(&new))
		return (ft_lstclear(&new, &free), 1);
	if (ft_lstsize(new) != 1)
		return (ft_lstclear(&new, &free),
			ft_putstr_fd("ambiguous redirection\n", 2), 1);
	remove_extra_nodes(file, file_end);
	free(file->content);
	file->content = new->content;
	return (free(new->mask), free(new), 0);
}
