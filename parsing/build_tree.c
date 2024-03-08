/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:20:58 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/06 15:24:57 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree *insert_tree(t_list *list, t_tree **root)
{
	t_list *tmp;
	t_list *tmp2;

	if (!list)
		return (*root);
	t_tree *new_node = malloc(sizeof(t_tree));
	if (!new_node)
		return NULL;
	new_node->node = list;
	if (tree_set_io(new_node))
		return NULL;
	remove_parenthesis(&list);
	tmp = find_roottree(&list);
	if (tmp)
	{
		new_node->node = tmp;
		tmp2 = tmp->next;
		tmp->next = NULL;
		new_node->left = NULL;
		new_node->right = NULL;
		*root = new_node;
		new_node->left = insert_tree(list, &(new_node->left));
		new_node->right = insert_tree(tmp2, &(new_node->right));
	}
	else
	{
		new_node->node = list;
		new_node->left = NULL;
		new_node->right = NULL;
		*root = new_node;
	}
	return *root;
}

t_tree *build_tree(t_list *list)
{
	t_tree *root;

	root = NULL;
	root = insert_tree(list, &root);
	if (!root)
		return (NULL);
	return (root);
}

void inheritance_bottom(t_tree *root)
{
	if (root->left == NULL && root->right == NULL)
		handle_redirections_bottom(root);
	else
	{
		inheritance_bottom(root->left);
		inheritance_bottom(root->right);
	}
}
