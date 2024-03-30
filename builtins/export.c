/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:35:14 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/30 02:07:49 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

static int	export_all_args(t_list *start, t_list **local_env)
{
	int	return_value;

	return_value = 0;
	while (start)
	{
		if (check_export_syntax(start->content))
		{
			if (add_export_node(start, local_env))
				return (1);
		}
		else
			return_value = 1;
		start = start->next;
	}
	return (return_value);
}

int	handle_export_no_args(t_list *local_env, t_tree *root)
{
	int		fd;
	t_list	*tmp;
	int		status;

	if (set_fd(&fd, root))
		return (ft_putstr_fd("export: error opening file\n", fd), 1);
	tmp = copy_lst(local_env);
	if (!tmp && local_env)
		return (ft_memset(&status, EXIT_FILENOTEXIST, 2), status);
	if (print_export(tmp, fd))
		return (ft_lstclear(&tmp, &free), ft_memset(&status, EXIT_FILENOTEXIST,
				2), status);
	ft_lstclear(&tmp, &free);
	return (0);
}

// allocs: local_env
int	ft_export(t_tree *root, char **env, int init)
{
	static t_list	*local_env = NULL;
	t_list			*tmp;
	int				status;

	status = 0;
	if (init)
		return (init_envs(&local_env, env));
	tmp = root->node;
	tmp = tmp->next;
	if (tmp)
	{
		if (export_all_args(tmp, &local_env))
			return (ft_memset(&status, EXIT_FILENOTEXIST, 2), status);
	}
	else
		return (handle_export_no_args(local_env, root));
	return (0);
}

int	change_env_value(t_list *node, char *key, char *value)
{
	char	*tmp;

	free(node->content);
	tmp = key;
	key = ft_strjoin(key, "=");
	free(tmp);
	if (!key)
		return (perror("change_env_value"), 1);
	tmp = value;
	value = ft_strjoin(key, value);
	free(key);
	free(tmp);
	if (!value)
		return (perror("change_env_value"), 1);
	node->content = ft_strdup(value);
	if (node->content == NULL)
		return (perror("change_env_value"), 1);
	free(value);
	return (0);
}

int	check_export_syntax(char *content)
{
	char	*eq;

	if (!content[0])
		return (ft_putstr_fd("export: not a valid identifier\n", 2), 0);
	eq = ft_strchr(content, '=');
	if (eq && eq != content && *(eq - 1) == '+')
		eq--;
	if (content == eq)
		return (ft_putstr_fd("export: not a valid identifier\n", 2), 0);
	else if (!is_valid_arg_name(content, eq))
		return (ft_putstr_fd("export: not a valid identifier\n", 2), 0);
	return (1);
}
