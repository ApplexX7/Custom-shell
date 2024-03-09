/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:02:47 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/09 18:04:03 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing/minishell.h"

t_tree *spown_tree(t_list *lst)
{
	t_tree *root;

	if (!lst)
		return (NULL);
	if (ft_open_herdocs(lst))
		return (NULL);
	root = build_tree(lst);
	if (!root)
		return (NULL);
	return (root);
}

t_tree *parsing_check(char *promt, char **env, int *status_code)
{
	t_list *lst;
	t_tree *root;

	lst = split_tokens(promt);
	if (!lst)
		return (NULL);
	lable_list(lst);
	if (split_env_arg(&lst))
		return (ft_lstclear(&lst, &free), NULL);
	if (expand_args(&lst, env))
		return (ft_lstclear(&lst, &free), NULL);
	*status_code = check_syntax(lst);
	if (*status_code != 0)
		return (ft_lstclear(&lst, &free), NULL);
	if (combine_list(&lst))
		return (ft_lstclear(&lst, &free), NULL);
	if (expand_wildcard(&lst))
		return (ft_lstclear(&lst, &free), NULL);
	labling_prio(lst);
	del_spaces(&lst);
	root = spown_tree(lst);
	if (!root)
		return (ft_lstclear(&lst, &free), NULL);
	return (root);
}

int executing_part(t_tree *root, int *status_code, char **env)
{
	int code;

    if (open_pipes(root))
		return (0);
	*status_code = executing_tree(root, env);
	code = manage_pid(0, WAIT, status_code);
	manage_fds(0, CLOSE);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	char *promt;
	static int status_code;
	t_tree *root;

	(void) argc;
	(void) argv;
	status_code = 0;
	while (1)
	{
		promt = readline("minishell %% ");
		root = parsing_check(promt, env, &status_code);
		if (root)
		{
			status_code = executing_part(root, &status_code, env);
			freetree(&root);
		}
		add_history(promt);
		free(promt);
	}
}
