/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:05:23 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/01 10:57:05 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void treeprint(t_tree *root1, int level)
{
	t_tree *root;

	root = root1;
    if (root == NULL)
             return;
	for (int i = 0; i < level; i++)
        printf(i == 0 ? "|-" : "   ");
	if (root->node != NULL)
	{
		t_list *tmp;

		tmp = root->node;
		printf("%s / %s / %d ", root->input_file, root->output_file, root->fd);
		while (tmp)
		{
 			printf("%s\t", (char *)tmp->content);
			if ((!ft_strncmp(tmp->content, ">", 2) || !ft_strncmp(tmp->content, ">>", 3))&& !tmp->is_op)
			{
				printf(" %s", tmp->fd_output);
			}
			else if (!ft_strncmp(tmp->content, "<", 2))
			{
				printf(" %s", tmp->fd_input);
			}
			else if (!ft_strncmp(tmp->content, "<<", 3))
			{
				printf(" %d", tmp->fd_herdoc);
			}
			tmp = tmp->next;
		}
		printf("\n");
	}
	else
		printf("[NULL]\n");
	treeprint(root->left, level + 1);
	treeprint(root->right, level + 1);
}

void print_ouput(t_list *node)
{
	while (node != NULL)
	{
		printf("%s ", (char *)node->content);
		if ((!ft_strncmp(node->content, "<<", 3) || !ft_strncmp(node->content, ">", 2) || !ft_strncmp(node->content, "<", 2) || !ft_strncmp(node->content, ">>", 3))&& !node->is_op)
			printf(" %s", node->fd_output);
		printf("\n");
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
