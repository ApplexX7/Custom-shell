/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:02:47 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/06 11:53:21 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing/minishell.h"

int main(int argc, char **argv, char **env)
{
	char *promt;
	t_list *lst;
	// t_list *copy;
	// t_tree *root;

	(void) argc;
	(void) argv;
	while (1)
	{
		promt = readline("minishell %% ");
		lst = split_tokens(promt);
		if (lst) // TODO: handle error printing
		{	
			lable_list(lst);
			if (expand_args(&lst, env))
				return (ft_lstclear(&lst, &free), 1); // TODO: handle error
			if (check_syntax(lst))
			{
				free(promt);
				continue ;
			}
			// if (combine_list(&lst))
			// 	return (ft_lstclear(&lst, &free), 1); // TODO: handle error
			// 										  //print_ouput(lst);
			// if (expand_wildcard(&lst))
			// 	return (ft_lstclear(&lst, &free), 1);
			// labling_prio(lst);
			// del_spaces(&lst);
			// if (ft_open_herdocs(lst) == 1)
			// {
			// 	ft_lstclear(&lst, &free);
			// 	continue ;
			// }
			// root = build_tree(lst);
			// if (!root)
			// 	return 0;
      		// if (open_pipes(root))
	  		// 	return (0);
			// inheritance_bottom(root);
			// executing_tree(root, env);
			// waitpid(-1, NULL, 0);
			// manage_pid(-1, WAIT);
			// manage_fds(-1, CLOSE);
			// add_history(promt);
			// treeprint(root, 0);
			// freetree(&root);
			free(promt);
			// ft_lstclear(&copy, &free);
		}
	}
}
