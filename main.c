/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:02:47 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/11 15:45:42 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing/minishell.h"

int main(int argc, char **argv, char **env)
{
	char *promt;
	int code;
	static int status_code;
	t_list *lst;
	t_tree *root;

	(void) argc;
	(void) argv;
	(void) env;
	status_code = 0;
  test_export();
	while (1)
	{
		promt = readline("minishell %% ");
		lst = split_tokens(promt);
		if (lst) // TODO: handle error printing
		{	
			lable_list(lst);
			if (split_env_arg(&lst))
				return (ft_lstclear(&lst, &free), 1); // TODO: handle error
			if (expand_args(&lst, env))
				return (ft_lstclear(&lst, &free), 1);
			status_code =  check_syntax(lst); // TODO: handle error
			if (status_code)
			{
				printf("status == %d\n", status_code);
				ft_lstclear(&lst, &free);
				free(promt);
				continue ;
			}
			if (combine_list(&lst))
				return (ft_lstclear(&lst, &free), 1); // TODO: handle error
			if (expand_wildcard(&lst))
				return (ft_lstclear(&lst, &free), 1);
			labling_prio(lst);
			del_spaces(&lst);
			if (ft_open_herdocs(lst) == 1)
			{
				ft_lstclear(&lst, &free);
				continue ;
			}
			root = build_tree(lst);
			if (!root)
				return 0;
      		if (open_pipes(root))
	  			return (0);
			// treeprint(root, 0);
			status_code = executing_tree(root, env);
			code = manage_pid(0 , WAIT, &status_code);
			manage_fds(0, CLOSE);
			add_history(promt);
			freetree(&root);
			// ft_lstclear(&lst, &free);
			//free(promt);
		}
		free(promt);
	}
}
