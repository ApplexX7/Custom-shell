/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:35:14 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/29 23:38:42 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

static int	export_all_args(t_list *start, t_list **local_env)
{
	int return_value;

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

// allocs: local_env
int	ft_export(t_tree *root, char **env, int init)
{
	static t_list	*local_env = NULL;
	t_list			*tmp;
	int				status;
	int				fd;

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
	{
		if (set_fd(&fd, root))
			return (ft_putstr_fd("export: error opening file\n", fd), 1);
		tmp = copy_lst(local_env);
		if (!tmp && local_env)
			return (ft_memset(&status, EXIT_FILENOTEXIST, 2), status);
		if (print_export(tmp, fd))
			return (ft_lstclear(&tmp, &free),ft_memset(&status, EXIT_FILENOTEXIST, 2), status);
		ft_lstclear(&tmp, &free);
	}
	return (0);
}

int	search_and_add(t_list **local_env, char *key, char *value)
{
	t_list	*lst;
	char *tmp;

	lst = *local_env;
	while (lst)
	{
		if (!ft_strncmp(lst->content, key, min(ft_strlen(key),
					ft_strlen(lst->content))))
		{
			free(lst->content);
			tmp = key;
			key = ft_strjoin(key, "=");
			free(tmp);
			if (!key)
				return (perror("search_and_add"), 1);
			tmp = value;
			value = ft_strjoin(key, value);
			free(key);
			free(tmp);
			if (!value)
				return (perror("search_and_add"), 1);
			lst->content = ft_strdup(value);
			if (lst->content == NULL)
				return (perror("search_and_add"), 1);
			free(value);
			return (0);
		}
		lst = lst->next;
	}
	if (export_add_key_value(local_env, key, value))
		return (ft_putstr_fd("export: error adding new entry\n", 2), 1);
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

// allocs: new
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

/*
int	main(int argc, char **argv, char **env)
{
  t_list *node;
	t_tree	t;

  node = NULL;
  ft_lstadd_back(&node, ft_lstnew("export"));
  ft_lstadd_back(&node, ft_lstnew("hello=ssss"));
  ft_lstadd_back(&node, ft_lstnew("world="));
  ft_lstadd_back(&node, ft_lstnew("=hello"));
  ft_lstadd_back(&node, ft_lstnew("=hello"));
  ft_lstadd_back(&node, ft_lstnew("a=hello"));
  ft_lstadd_back(&node, ft_lstnew("aaaa=hello"));
  ft_lstadd_back(&node, ft_lstnew("aa-aa=hello"));
  ft_lstadd_back(&node, ft_lstnew("aaaa+=hello"));
  ft_lstadd_back(&node, ft_lstnew("aaaa+=hello"));
  ft_lstadd_back(&node, ft_lstnew("aaaa+=hello"));
  ft_lstadd_back(&node, ft_lstnew("testest+=hello"));
  ft_lstadd_back(&node, ft_lstnew("aaaa=hello"));
  ft_lstadd_back(&node, ft_lstnew("arg"));
  t = {node, NULL, NULL, 0, 1, NULL, NULL};
  ft_export(&t, env);
  //ft_lstclear(&node, &free);
  node = NULL;
  ft_lstadd_back(&node, ft_lstnew("export"));
  t.node = node;
  ft_export(&t, env);
  printf("====================\n");
  ft_env(&t, NULL);
}
*/
