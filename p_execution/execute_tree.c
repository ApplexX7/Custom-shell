/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:45:48 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/23 18:04:03 by mohilali         ###   ########.fr       */
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
	return (0);
}

int execute_builtins(t_tree *root, char **env)
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
	return (0);
}

int ft_expand_combine(t_tree *root)
{
	(void)root;
	if (expand_args(&root->node))
		return (1);
	if (expand_wildcard(&root->node))
		return (1);
	return (0);
}

int	executing_tree(t_tree *root, char **env)
{
	int status_code = 0;

	if (root->left == NULL && root->right == NULL)
	{
		if (inheritance_bottom(root))
			return (1);
		if (ft_expand_combine(root))
			return (1);
		if (!root->fbuiltins && its_builtins(root))
			return (execute_builtins(root, env));
		else
			if (create_chdilren(root, env))
				return (1);
	}
	else if (is_andor(root))
		status_code  = check_operators(root, env);
	else
	{
		if (executing_tree(root->left, env))
			return (1);
		if (executing_tree(root->right, env))
			return (1);
	}
	return (status_code);
}
