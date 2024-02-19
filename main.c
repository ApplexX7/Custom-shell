/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:02:47 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/19 15:12:34 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/minishell.h"

int main(int argc, char **argv, char **env)
{
    char *promt;
	t_list *lst;
	t_list *tmp;

	(void) argc;
	(void) argv;
    while (1)
    {
        promt = readline("minishell %% ");
        lst = split_tokens(promt);
		if (!lst) // TODO: handle error printing
			return (1);
		lable_list(lst);
		tmp = expand_args(&lst, env);
		ft_lstclear(&lst, &free);
		if (tmp == NULL)
			return (1); // TODO: handle error
		lst = tmp;
		print_ouput(lst);
    }
}
