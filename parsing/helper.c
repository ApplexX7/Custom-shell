/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:10:28 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/30 02:27:02 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freetree(t_tree **root)
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

void	syntax_error_handling(t_list *copy)
{
	ft_lstclear(&copy, &free);
	printf("bash: syntax error in tokens\n");
}

t_list	*skip_spaces(t_list *start)
{
	while (start && is_space(start))
		start = start->next;
	return (start);
}
