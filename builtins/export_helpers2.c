/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:46:43 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/30 03:49:38 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	init_local_env(t_list **local_env, char **env)
{
	t_list	*new;
	int		i;

	new = NULL;
	i = 0;
	while (env[i])
	{
		if (new_and_add(&new, env[i], '\''))
			return (ft_lstclear(&new, &free), 1);
		i++;
	}
	*local_env = new;
	return (0);
}

// closes fd at end
int	print_export(t_list *lst, int fd)
{
	char	*eq;

	bubblesort(lst);
	while (lst)
	{
		ft_putstr_fd("declare -x ", fd);
		eq = ft_strchr(lst->content, '=');
		if (!eq)
		{
			ft_putstr_fd(lst->content, fd);
			ft_putstr_fd("\n", fd);
		}
		else
		{
			ft_putnstr_fd(lst->content, fd, eq - (char *)lst->content + 1);
			ft_putstr_fd("\"", fd);
			ft_putstr_fd(eq + 1, fd);
			ft_putstr_fd("\"\n", fd);
		}
		lst = lst->next;
	}
	if (fd != 1 && ft_close(fd) == -1)
		return (perror("close"), 1);
	return (0);
}

// allocs: new
// frees key and value
// add value to key in dest
int	export_add_key_value(t_list **dest, char *key, char *value)
{
	char	*new;
	char	*tmp;

	tmp = key;
	if (value)
	{
		tmp = ft_strjoin(key, "=");
		free(key);
	}
	if (!tmp)
		return (perror("export_add_key_value"), 1);
	new = tmp;
	if (value)
	{
		new = ft_strjoin(tmp, value);
		(free(value), free(tmp));
		if (!new)
			return (perror("export_add_key_value"), 1);
	}
	if (new_and_add(dest, new, '\''))
		return (free(new), ft_putstr_fd("export: error adding new entry\n", 2),
			1);
	free(new);
	return (0);
}

// init local_env in function that uses it
int	init_envs(t_list **local_env, char **env)
{
	get_exported_arg_value(NULL, local_env, 0);
	ft_env(NULL, local_env);
	ft_unset(NULL, local_env);
	add_env_arg(NULL, NULL, local_env);
	get_local_env_representation(local_env, NULL);
	if (init_local_env(local_env, env))
		return (perror("init_local_env: malloc"), 1);
	return (0);
}
