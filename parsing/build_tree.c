/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:20:58 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/04 17:13:36 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void inherente_reidirections(t_tree *root, char *output, char *input, int fd)
{
	if (root == NULL)
		return ;
	if(root->input_file  == NULL)
		root->input_file = input;
	if (root->output_file == NULL)
		root->output_file = output;
	if (root->fd == 0)
		root->fd = fd;
	inherente_reidirections(root->left, root->output_file, root->input_file, root->fd);
	inherente_reidirections(root->right, root->output_file, root->input_file, root->fd);
}

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
		handle_redirections_bottom(new_node);
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
	inherente_reidirections(root, root->output_file, root->input_file, root->fd);
	return (root);
}
