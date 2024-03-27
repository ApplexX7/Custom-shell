/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:10:28 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/27 17:45:40 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void freetree(t_tree **root)
{
	if (!(*root))
		return ;
	freetree(&(*root)->right);
	freetree(&(*root)->left);
	ft_lstclear(&(*root)->node, &free);
	ft_lstclear(&(*root)->input_files, &free);
	ft_lstclear(&(*root)->output_files, &free);
	free((*root)->input_file);
	free((*root)->output_file);
	free((*root));
	*root = NULL;
}


void	appendto_list(t_list *source, t_list **dest)
{
	t_list	*tmp;

	while (source)
	{
		tmp = source;
		source = source->next;
		tmp->next = NULL;
		ft_lstadd_back(dest, tmp);
	}
}

void	status_code_of_syntax_error(int *status_code)
{
	ft_memset(status_code, 0, 4);
	ft_memset(status_code, 1, 3);
	ft_memset(status_code, 2, 2);
}

/*
void lst_remove_node(t_list **lst, t_list *node)
{
	t_list *tmp;

	tmp = *lst;
	if (tmp == node)
	{
		*lst = node->next;
		ft_lstdelone(node, &free);
	}
	while (tmp->next)
	{
		if (tmp->next == node)
		{
			tmp->next = node->next;
			ft_lstdelone(node, &free);
			return ;
		}
		tmp = tmp->next;
	}
}
*/

/*
int is_space(t_list *node)
{
	if (!strncmp(node->content, " ", 2) && !node->is_op)
		return (1);
	else
		return (0);
}
*/

/*
void del_spaces(t_list **lst)
{
	t_list *tmp;
  t_list *tmp2;

	tmp = *lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (is_space(tmp))
		{
			lst_remove_node(lst, tmp);
			tmp = tmp2;
		}
		tmp = tmp2;
	}
}
*/

t_list *skip_spaces(t_list *start)
{
	while (start && is_space(start))
		start = start->next;
	return (start);
}

int is_parentis(t_list *node)
{
	if (!ft_strncmp(node->content, "(", 2) && !node->is_op)
		return (1);
	if (!ft_strncmp(node->content, ")", 2) && !node->is_op)
		return (1);
	return (0);
}

void del_parentis(t_list **lst)
{
	t_list *tmp;
  t_list *tmp2;

	tmp = *lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (is_parentis(tmp))
		{
			lst_remove_node(lst, tmp);
			printf("hr\n");
			// tmp = tmp2;
		}
		tmp = tmp2;
	}
}
