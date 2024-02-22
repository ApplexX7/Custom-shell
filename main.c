/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:02:47 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/22 13:50:46 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/minishell.h"

int main(int argc, char **argv, char **env)
{
	char *promt;
	t_list *lst;

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
			if (check_syn(lst))
				continue ;
			if (combine_list(&lst))
				return (ft_lstclear(&lst, &free), 1); // TODO: handle error
			print_ouput(lst);
			print_ouput_op(lst);
      expand_wildcard(&lst);
		}
		// print_ouput_op(lst);
	}
}
