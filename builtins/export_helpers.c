/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:40:59 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/28 17:55:07 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	add_env_arg(char *key, char *value, t_list **env)
{
	static t_list	**local_env = NULL;

	if (env)
		local_env = env;
	else
	{
		return (search_and_add(local_env, key, value));
	}
	return (0);
}

char	*get_exported_arg_value(char *arg, t_list **local_lst, int free_bit)
{
	static t_list	**lst = NULL;
	t_list			*tmp;

	if (free_bit)
		(ft_lstclear(lst, &free), *lst = NULL);
	else if (local_lst)
		lst = local_lst;
	else if (lst)
	{
		tmp = *lst;
		while (tmp)
		{
			if (!ft_strncmp(arg, tmp->content, ft_strlen(arg))
				&& ((char *)tmp->content)[ft_strlen(arg)] == '=')
				return ((char *)tmp->content + ft_strlen(arg) + 1);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

// allocs: key, value
int	add_export_node(t_list *lst, t_list **local_env)
{
	char	*key;
	char	*value;
	int		join;

	join = 0;
	get_key_value(lst->content, &key, &value, &join);
	if (join)
	{
		if (concat_and_add(key, value, local_env))
			return (1);
	}
	else
	{
		if (search_and_add(local_env, key, value))
			return (free(key), free(value),
				ft_putstr_fd("export: error adding new entry\n", 2), 1);
	}
	return (0);
}

int	is_valid_arg_name(char *start, char *end)
{
	if (ft_isdigit(*start))
		return (0);
	while (start < end || (!end && *start))
	{
		if (!ft_isalpha(*start) && !ft_isdigit(*start) && *start != '_')
			return (0);
		start++;
	}
	return (1);
}

// allocs: key, value
// set key and value from content
int	get_key_value(char *content, char **key, char **value, int *join)
{
	char	*eq;
	char	*k;
	char	*v;

	eq = ft_strchr(content, '=');
	if (key)
		k = ft_substr(content, 0, eq - content);
	if (value && eq)
		v = ft_substr(eq, 1, ft_strlen(eq) - 1);
	if (key && k)
	{
		if (k[ft_strlen(k) - 1] == '+')
		{
			if (join)
				*join = 1;
			k[ft_strlen(k) - 1] = '\0';
		}
	}
	if (key)
		*key = k;
	if (!eq)
		*value = NULL;
	else if (value)
		*value = v;
	return (0);
}
