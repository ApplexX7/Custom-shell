/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:45:48 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/25 21:42:48 by mohilali         ###   ########.fr       */
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

int execute_andoperator(t_tree *root, char **env, t_tree *head_of_root)
{
	int input;
	int output;
	int status;

	input = 0;
	output = 1;
	if (ft_dup_parent(root))
		return (-1);
	input = root->fd;
	output = root->out_fd;
	status = executing_tree(root->left, env, head_of_root);
	manage_pid(0, WAIT, &status);
	if (WEXITSTATUS(status) ==  0)
		status = executing_tree(root->right, env, head_of_root);
	set_back_io(input, output);
	return (status);
}

int execute_or_operatore(t_tree *root , char **env, t_tree *head_of_root)
{
	int input;
	int output;
	int status;

	input = 0;
	output = 1;
	if (ft_dup_parent(root))
		return (-1);
	input = root->fd;
	output = root->out_fd;
	status = executing_tree(root->left, env, head_of_root);
	manage_pid(0, WAIT, &status);
	if (WEXITSTATUS(status))
		status = executing_tree(root->right, env, head_of_root);
	set_back_io(input, output);
	return (status);
}

int check_operators(t_tree *root ,char **env, t_tree *head_of_root)
{
	int status = 0;

	if (!ft_strncmp(root->node->content, "&&", 3) && !root->node->is_op)
	{
		status = execute_andoperator(root, env, head_of_root);
		if (status)
			return (status);
	}
	else if (!ft_strncmp(root->node->content, "||", 3) && !root->node->is_op)
	{
		status = execute_or_operatore(root, env, head_of_root);
		if (status)
			return (status);
	}
	return (0);
}


int its_builtins(t_tree *root)
{
	if (!root || !root->node)
		return (0);
	if (!ft_strncmp(root->node->content, "echo", 5))
		return (1);
	if (!ft_strncmp(root->node->content, "export", 7))
		return (1);
	if (!ft_strncmp(root->node->content, "env", 4))
		return (1);
	if (!ft_strncmp(root->node->content, "cd", 3))
		return (1);
	if (!ft_strncmp(root->node->content, "unset", 6))
		return(1);
	if (!ft_strncmp(root->node->content, "pwd", 4))
		return(1);
	if (!ft_strncmp(root->node->content, "exit", 5))
		return(1);
	return (0);
}

int execute_builtins(t_tree *root, char **env, t_tree *head_of_tree)
{
	if (!ft_strncmp(root->node->content, "echo", 5))
		return (ft_echo(root));
	if (!ft_strncmp(root->node->content, "export", 7))
		return (ft_export(root, env, 0));
	if (!ft_strncmp(root->node->content, "env", 4))
		return (ft_env(root, NULL));
	if (!ft_strncmp(root->node->content, "cd", 3))
		return(ft_cd(root));
	if (!ft_strncmp(root->node->content, "unset", 6))
		return(ft_unset(root, NULL));
	if (!ft_strncmp(root->node->content, "pwd", 4))
		return(ft_pwd(root));
	if (!ft_strncmp(root->node->content, "exit", 5))
		return(ft_exit(root, head_of_tree));
	return (0);
}

int ft_expand_combine(t_tree *root)
{
	if (expand_args(&root->node))
		return (1);
	return (0);
}

int	executing_tree(t_tree *root, char **env, t_tree *head_of_root)
{
	int status_code = 0;

	if (root->left == NULL && root->right == NULL)
	{
		if (expand_wildcard(&root->node))
			return (1);
		if (inheritance_bottom(root))
			return (1);
		if (ft_expand_combine(root))
			return (1);
		if (!root->fbuiltins && its_builtins(root))
			return (execute_builtins(root, env, head_of_root));
		else
			if (create_chdilren(root, env, head_of_root))
				return (1);
	}
	else if (is_andor(root))
		status_code  = check_operators(root, env, head_of_root);
	else
	{
		if (executing_tree(root->left, env, head_of_root))
			return (1);
		if (executing_tree(root->right, env, head_of_root))
			return (1);
	}
	return (status_code);
}
