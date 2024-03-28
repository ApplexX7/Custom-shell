/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:32:09 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/27 17:39:25 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	donothing(void *arg)
{
	(void)arg;
}

t_list	*convert_to_list(char **arr)
{
	int		i;
	t_list	*new;
	t_list	*node;

	new = NULL;
	i = 0;
	while (arr[i])
	{
		node = ft_lstnew(arr[i]);
		if (!node)
			return (ft_lstclear(&new, &donothing), NULL);
		ft_lstadd_back(&new, node);
		i++;
	}
	return (new);
}

int	addback_node(t_list **dest, t_list *node)
{
	char	*content;
	t_list	*new_node;

	content = ft_strdup(node->content);
	if (!content)
		return (1);
	new_node = ft_lstnew(content);
	if (!new_node)
		return (free(content), 1);
	ft_lstadd_back(dest, new_node);
	return (0);
}

void	lst_delete_node(t_list **lst, t_list *node)
{
	t_list	*right_node;

	right_node = get_right_node(*lst, node);
	if (right_node)
		right_node->next = node->next;
	if (*lst == node)
		*lst = node->next;
	ft_lstdelone(node, &free);
}

int	add_env_args(char *arg, t_list **dest)
{
	char	**arr;
	t_list	*new_lst;

	arr = ft_split(arg, ' ');
	if (!arr)
		return (1);
	new_lst = convert_to_list(arr);
	if (!new_lst)
		return (free_2d_arr((void **)arr), 1);
	appendto_list(new_lst, dest);
	free(arr);
	return (0);
}
