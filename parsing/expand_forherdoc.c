/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_forherdoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:21:49 by mohilali          #+#    #+#             */
/*   Updated: 2025/02/27 11:10:20 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_to_front(t_list **source, t_list *dest)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *source;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		tmp2->next = NULL;
		ft_lstadd_back(&dest, tmp2);
	}
	*source = dest;
}

char	*get_envarg_value(char *arg)
{
	char	*value;

	arg++;
	value = get_exported_arg_value(arg, NULL, 0);
	if (value)
		return (value);
	else
		return (NULL);
}

t_list	*get_right_node(t_list *head, t_list *node)
{
	if (head == node)
		return (NULL);
	while (head->next != node)
		head = head->next;
	return (head);
}

static int	handle_single_dolor(t_list *node, t_list **dest)
{
	if (!ft_strncmp(node->content, "$", 2))
		return (addback_node(dest, node));
	else
		return (0);
}

int	expand_herdoc(t_list **lst)
{
	t_list	*tmp;
	t_list	*new;

	tmp = *lst;
	new = NULL;
	while (tmp)
	{
		if (ft_strchr(tmp->content, '$'))
		{
			if (get_envarg_value(tmp->content)
				&& ft_strncmp(tmp->content, "$", 2))
			{
				if (add_env_args(get_envarg_value(tmp->content), &new))
					return (ft_lstclear(&new, &free), 1);
			}
			else if (handle_single_dolor(tmp, &new))
				return (ft_lstclear(&new, &free), 1);
		}
		else if (addback_node(&new, tmp))
			return (ft_lstclear(&new, &free), 1);
		tmp = tmp->next;
	}
	return (ft_lstclear(lst, &free), *lst = new, 0);
}
