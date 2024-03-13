/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:05:23 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/13 14:32:45 by ayait-el         ###   ########.fr       */
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
	printf("%s / %s / %d / %d ", root->input_file, root->output_file, root->fd, root->out_fd);
	if (root->node != NULL)
	{
		t_list *tmp;

		tmp = root->node;
		while (tmp)
		{
 			printf("%s\t", (char *)tmp->content);
 			// printf("%c\t", (char )tmp->is_op);
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
			printf(" %d", node->fd);
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

void test_export(char **env)
{
  t_list *node;
  node = NULL;
  ft_lstadd_back(&node, ft_lstnew(ft_strdup("export")));
  ft_lstadd_back(&node, ft_lstnew(ft_strdup("hello=ssss")));
  ft_lstadd_back(&node, ft_lstnew(ft_strdup("world=")));
  ft_lstadd_back(&node, ft_lstnew(ft_strdup("=hello")));
  ft_lstadd_back(&node, ft_lstnew(ft_strdup("=hello")));
  ft_lstadd_back(&node, ft_lstnew(ft_strdup("a=hello")));
  ft_lstadd_back(&node, ft_lstnew(ft_strdup("aaaa+=hello")));
  ft_lstadd_back(&node, ft_lstnew(ft_strdup("aaaa+=hello")));
  t_tree t = {node, NULL, NULL, 0, 1, NULL, NULL, 0};
  ft_export(&t, env);
  //ft_lstclear(&node, &free);
  //node = NULL;
  // ft_lstadd_back(&node, ft_lstnew("export"));
  //t.node = node;
  //ft_export(&t);
}
