/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 20:01:09 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/27 22:48:38 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// this function shouldn't fail
static int	handle_digit_arg(t_list *node)
{
	char	*tmp;

	if (ft_isdigit(((char *)node->content)[1]))
	{
		tmp = &((char *)node->content)[2];
		if (*tmp == '\0')
			return (1);
		ft_memmove(node->content, tmp, ft_strlen(tmp) + 1);
		return (1);
	}
	return (0);
}

void	skip_alpha_digit_inderscore(char **content)
{
	while (ft_isalpha(**content) || ft_isdigit(**content) || **content == '_')
		(*content)++;
}

// split env arg: $=== -> "$", "==="
int	split_env_arg_and_add(t_list *node, t_list **dest, char *content)
{
	char	*tmp;

	tmp = ft_substr(node->content, 0, content - (char *)node->content);
	if (!tmp || new_and_add(dest, tmp, node->is_op))
		return (free(tmp), 1);
	free(tmp);
	if (new_and_add(dest, content, node->is_op))
		return (1);
	return (0);
}

// allocs: tmp
int	split_arg_node(t_list *node, t_list **dest)
{
	char	*content;

	if (handle_digit_arg(node))
		return (add_node(dest, node));
	content = node->content;
	content++;
	if (*content == '?')
		content++;
	else
		skip_alpha_digit_inderscore(&content);
	if (*content == '\0')
	{
		if (new_and_add(dest, node->content, node->is_op))
			return (1);
	}
	else if (content - (char *)node->content == 1)
	{
		if (new_and_add(dest, node->content, '\''))
			return (1);
	}
	else if (split_env_arg_and_add(node, dest, content))
		return (1);
	return (0);
}

// allocs: new
// frees lst on sucess
int	split_env_arg(t_list **lst)
{
	t_list	*tmp;
	t_list	*new;

	tmp = *lst;
	new = NULL;
	while (tmp)
	{
		if (ft_strchr(tmp->content, '$'))
		{
			if (tmp->is_op != '\'')
			{
				if (split_arg_node(tmp, &new))
					return (ft_lstclear(&new, &free), 1);
			}
			else if (add_node(&new, tmp))
				return (ft_lstclear(&new, &free), 1);
		}
		else if (add_node(&new, tmp))
			return (ft_lstclear(&new, &free), 1);
		tmp = tmp->next;
	}
	ft_lstclear(lst, &free);
	*lst = new;
	return (0);
}
