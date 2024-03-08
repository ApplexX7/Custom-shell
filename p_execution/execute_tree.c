/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:45:48 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/08 12:44:55 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void handle_error()
{
	perror("Error :");
}

int transfer_todoublearr(t_list *list)
{
	int len;
	t_list *lst;

	len = 0;
	lst = list;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

char **setup_command(t_tree *content)
{
	char **cmd;
	t_list *current;
	int index;
	int len;

	len = transfer_todoublearr(content->node);
	cmd = malloc(sizeof(char *) * (len + 1));
	if (!cmd)
	{
		printf("Filaed malloc!!\n");
		exit(1);
	}
	index = 0;
	current = content->node;
	while (current)
	{
		cmd[index] = ft_strdup(current->content);
		index++;
		current = current->next;
	}
	cmd[index] = 0;
	return (cmd);
}

int is_andor(t_tree *root)
{
	if (!ft_strncmp(root->node->content, "&&", 3) && !root->node->is_op)
		return (1);
	if (!ft_strncmp(root->node->content, "||", 3) && !root->node->is_op)
		return (1);
	return (0);
}

int check_operators(t_tree *root ,char **env)
{
	int save_state;
	int status;

	if (!ft_strncmp(root->node->content, "&&", 3) && !root->node->is_op)
	{
		save_state = ft_dup_parent(root);
		if (save_state == -1)
			return 0;
		executing_tree(root->left, env);
		status = manage_pid(0, WAIT);
		if (status == 0)
			executing_tree(root->right, env);
		set_back_io(save_state);
		return (status);
	}
	else if (!ft_strncmp(root->node->content, "||", 3) && !root->node->is_op)
	{
		save_state = ft_dup_parent(root);
		if (save_state == -1)
			return 0;
		executing_tree(root->left, env);
		status = manage_pid(0, WAIT);
		if (status != 0)
			executing_tree(root->right, env);
		set_back_io(save_state);
		return (status);
	}
	return (0);
}

int	executing_tree(t_tree *root, char **env)
{
	int status_code = 0;

	if (root->left == NULL && root->right == NULL)
	{
		inheritance_bottom(root);
		create_chdilren(root, env);
	}
	else if (is_andor(root))
		status_code  = check_operators(root, env);
	else
	{
		executing_tree(root->left, env);
		executing_tree(root->right, env);
	}
	return (status_code);
}
