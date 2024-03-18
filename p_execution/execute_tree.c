/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:45:48 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/18 17:08:25 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void handle_error()
{
	perror("minishell:");
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
	int input = 0;
	int output = 1;
	int save_state;
	int status;

	if (!ft_strncmp(root->node->content, "&&", 3) && !root->node->is_op)
	{
		save_state = ft_dup_parent(root);
		input = root->fd;
		output = root->out_fd;
		if (save_state == -1)
			return 0;
		status = executing_tree(root->left, env);
		manage_pid(0, WAIT, &status);
		if (status >> 8 ==  0)
			executing_tree(root->right, env);
		set_back_io(input, output);
		return (status);
	}
	else if (!ft_strncmp(root->node->content, "||", 3) && !root->node->is_op)
	{
		save_state = ft_dup_parent(root);
		input = root->fd;
		output = root->out_fd;
		if (save_state == -1)
			return 0;
		status = executing_tree(root->left, env);
		manage_pid(0, WAIT, &status);
		if (status >> 8 !=  0)
			executing_tree(root->right, env);
		set_back_io(input, output);
		return (status);
	}
	return (0);
}


int its_builtins(t_tree *root)
{
	if (!root || !root->node)
		return (0);
	if (!ft_strncmp(root->node->content, "echo", 4))
		return (1);
	if (!ft_strncmp(root->node->content, "export", 6))
		return (1);
	if (!ft_strncmp(root->node->content, "env", 3))
		return (1);
	if (!ft_strncmp(root->node->content, "cd", 2))
		return (1);
	return (0);
}

int execute_builtins(t_tree *root, char **env)
{
	if (!ft_strncmp(root->node->content, "echo", 4))
		ft_echo(root);
	if (!ft_strncmp(root->node->content, "export", 6))
		ft_export(root, env);
	if (!ft_strncmp(root->node->content, "env", 3))
		ft_env(root, NULL);
	if (!ft_strncmp(root->node->content, "cd", 2))
		ft_cd(root);
	return (0);
}

int	executing_tree(t_tree *root, char **env)
{
	int status_code = 0;

	if (root->left == NULL && root->right == NULL)
	{
		inheritance_bottom(root);
		if (!root->fbuiltins && its_builtins(root))
			return (execute_builtins(root, env));
		else
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
