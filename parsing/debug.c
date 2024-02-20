/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:05:23 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/19 20:13:45 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_ouput(t_list *node)
{
	while (node != NULL)
	{
		printf("%s\n", (char *)node->content);
		node = node->next;
	}
	printf("\n");
}

void print_ouput_op(t_list *node)
{
	while (node != NULL)
	{
		printf("%c\n", node->is_op);
		node = node->next;
	}
	printf("\n");
}
