/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:46:30 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/27 17:14:05 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int is_number(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int ft_exit(t_tree *node, t_tree *root_of_tree)
{
	int number;
	t_list *current;

	number = 0;
	current = node->node;
	if (current->next)
	{
		
		if (!is_number(current->next->content))
		{
			number = ft_atoi(current->next->content);
			if (ft_lstsize(node->node) > 2)
			{
				write(2,"minishell: exit: too many arguments\n", 36);
				return (EXIT_FILENOTEXIST);
			}
		}
		else
		{
			number = EXIT_ABOVETYPE;
			write(2,"minishell: exit: numeric argument required\n", 43);
		}
	}
	get_exported_arg_value(NULL, NULL, 1);
	freetree(&root_of_tree);
	exit(number);
}
