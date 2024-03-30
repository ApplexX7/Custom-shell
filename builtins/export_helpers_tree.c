/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 02:06:27 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/30 02:07:53 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	concat_and_add(char *key, char *value, t_list **local_env)
{
	char	*new;
	t_list	*tmp;

	tmp = *local_env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, key, min(ft_strlen(tmp->content),
					ft_strlen(key))))
		{
			new = ft_strjoin(tmp->content, value);
			(free(key), free(value));
			if (!new)
				return (perror("concat_and_add: malloc"), 1);
			free(tmp->content);
			tmp->content = new;
			return (0);
		}
		tmp = tmp->next;
	}
	if (export_add_key_value(local_env, key, value))
		return (perror("concat_and_add: malloc"), 1);
	return (0);
}

int	search_and_add(t_list **local_env, char *key, char *value)
{
	t_list	*lst;

	lst = *local_env;
	while (lst)
	{
		if (!ft_strncmp(lst->content, key, min(ft_strlen(key),
					ft_strlen(lst->content))))
		{
			if (change_env_value(lst, key, value))
				return (1);
			return (0);
		}
		lst = lst->next;
	}
	if (export_add_key_value(local_env, key, value))
		return (ft_putstr_fd("export: error adding new entry\n", 2), 1);
	return (0);
}
