/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:05:23 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/23 12:59:54 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void treeprint(t_tree *root)
{
    if (root == NULL)
             return;
	if (root->node != NULL)
	{
		while (root->node)
		{
 			printf("%s\n", (char *)root->node->content);
			root->node = root->node->next;
		}
		printf("------\n");
	}
	treeprint(root->left);
	treeprint(root->right);
}

void print_ouput(t_list *node)
{
	while (node != NULL)
	{
		printf("%s", (char *)node->content);
		printf(" %d\t", node->prio);
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
