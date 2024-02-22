/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:05:23 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/22 16:25:16 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_ouput(t_list *node)
{
	while (node != NULL)
	{
		printf("%s\t", (char *)node->content);
		node = node->next;
	}
	printf("\n");
}

void print_ouput_op(t_list *node)
{
	while (node != NULL)
	{
		printf("%d\t", (int)node->is_op);
		node = node->next;
	}
	printf("\n");
}
