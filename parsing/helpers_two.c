/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:19:21 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/28 17:21:05 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_remove_node(t_list **lst, t_list *node)
{
	t_list	*tmp;

	tmp = *lst;
	if (tmp == node)
	{
		*lst = node->next;
		ft_lstdelone(node, &free);
		return ;
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

// allocs: content, mask, new_node
int	add_node(t_list **dest, t_list *node)
{
	char	*content;
	t_list	*new_node;
	char	*mask;

	content = ft_strdup(node->content);
	if (!content)
		return (1);
	if (node->mask)
	{
		mask = ft_strdup(node->mask);
		if (!mask)
			return (free(content), 1);
	}
	else
		mask = NULL;
	new_node = ft_lstnew(content);
	if (!new_node)
		return (free(content), 1);
	new_node->is_op = node->is_op;
	new_node->fd = node->fd;
	new_node->mask = mask;
	ft_lstadd_back(dest, new_node);
	return (0);
}

int	ft_lstjoin(t_list *lst, char **dest)
{
	char	*tmp;
	char	*result;

	result = NULL;
	while (lst)
	{
		tmp = result;
		result = ft_strjoin(result, lst->content);
		free(tmp);
		if (!result && tmp)
			return (perror("ft_lstjoin"), 1);
		lst = lst->next;
	}
	*dest = result;
	return (0);
}

t_list	*convert_arr_to_list(char **arr)
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
			return (ft_lstclear(&new, &do_nothing), NULL);
		ft_lstadd_back(&new, node);
		i++;
	}
	return (new);
}

// allocs: str, new
// TODO: change this to have is_op passed as an arg
int	join_and_add(t_list **dest, t_list *start, t_list *end)
{
	t_list	*tmp;
	char	*str;
	t_list	*new;

	tmp = start;
	while (tmp->next != end)
		tmp = tmp->next;
	tmp->next = NULL;
	str = join_list(start);
	tmp->next = end;
	if (!str)
		return (1);
	new = ft_lstnew(str);
	if (!new)
		return (free(str), 1);
	new->is_op = start->is_op;
	if (join_mask(start, end, new))
		return (ft_lstdelone(new, &free), 1);
	ft_lstadd_back(dest, new);
	return (0);
}
