/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:02:47 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/20 18:28:42 by mohilali         ###   ########.fr       */
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
		if (!lst) // TODO: handle error printing
			return (1);
		lable_list(lst);
		if (expand_args(&lst, env))
			return (ft_lstclear(&lst, &free), 1); // TODO: handle error
		lable_list(lst);
		check_syn(lst);
		// print_ouput(lst);
		// print_ouput_op(lst);
    }
}
