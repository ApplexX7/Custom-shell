/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:33:08 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/29 18:39:58 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/minishell.h"

int	executing_part(t_tree *root, int *status_code, char **env)
{
	t_tree	*head_of_root;

	head_of_root = root;
	if (open_pipes(root))
		return (0);
	*status_code = executing_tree(root, env, head_of_root, status_code);
	manage_fds(0, CLOSE_ALL);
	manage_pid(0, WAIT, status_code);
	return (0);
}

t_tree	*spown_tree(t_list *lst)
{
	t_tree	*root;

	if (!lst)
		return (NULL);
	if (ft_open_herdocs(lst))
		return (NULL);
	root = build_tree(lst);
	if (!root)
		return (NULL);
	return (root);
}

t_tree	*parsing_check(char *promt, char **env, int *status_code)
{
	t_list	*lst;
	t_tree	*root;

	(void)env;
	lst = split_tokens(promt);
	if (!lst)
		return (NULL);
	add_history(promt);
	lable_list(lst);
	if (split_env_arg(&lst))
		return (ft_lstclear(&lst, &free), NULL);
	if (check_syntax(lst, status_code))
		return (ft_lstclear(&lst, &free), NULL);
	lable_env_args(lst);
	if (combine_list(&lst))
		return (ft_lstclear(&lst, &free), NULL);
	labling_prio(lst);
	//del_spaces(&lst);
	root = spown_tree(lst);
	if (!root)
		return (ft_lstclear(&lst, &free), NULL);
	return (root);
}

char	*get_cwd(void)
{
	size_t	size;
	char	*buffer;
	char	*path;

	size = PATH_MAX;
	buffer = malloc(sizeof(char) * size);
	if (!buffer)
		return (NULL);
	if (!getcwd(buffer, size))
		return (NULL);
	path = ft_strjoin("PWD=", buffer);
	if (!path)
		return (free(buffer), NULL);
	free(buffer);
	return (path);
}

int	init_minihsell_arg(int *status_code, char **env)
{
	
	get_env_value(NULL, status_code, NULL);
	tcgetattr(STDIN_FILENO, &g_original_terminos);
	recept_signals();
	if (!env || !env[0])
	{
		env = create_env();
		if (!env)
			return (0);
		ft_export(NULL, env, 1);
		free_2d_arr((void **)env);
	}
	else
		ft_export(NULL, env, 1);
	return (0);
}
