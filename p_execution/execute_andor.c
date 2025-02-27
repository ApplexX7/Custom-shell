/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_andor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:05:40 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/29 23:27:05 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	execute_andoperator(t_tree *root, char **env,
	t_tree *head_of_root, int *status)
{
	int	input;
	int	output;

	input = 0;
	output = 1;
	*status = 0;
	if (ft_dup_parent(root))
		return (-1);
	input = root->fd;
	output = root->out_fd;
	*status = executing_tree(root->left, env, head_of_root, status);
	manage_pid(0, WAIT, status);
	if (WEXITSTATUS(*status) == 0)
		*status = executing_tree(root->right, env, head_of_root, status);
	set_back_io(input, output);
	return (*status);
}

int	execute_or_operatore(t_tree *root, char **env,
	t_tree *head_of_root, int *status)
{
	int	input;
	int	output;

	input = 0;
	output = 1;
	*status = 0;
	if (ft_dup_parent(root))
		return (-1);
	input = root->fd;
	output = root->out_fd;
	*status = executing_tree(root->left, env, head_of_root, status);
	manage_pid(0, WAIT, status);
	if (WEXITSTATUS(*status))
		*status = executing_tree(root->right, env, head_of_root, status);
	set_back_io(input, output);
	return (*status);
}

int	check_operators(t_tree *root, char **env,
	t_tree *head_of_root, int *status)
{
	if (!ft_strncmp(root->node->content, "&&", 3) && !root->node->is_op)
	{
		*status = execute_andoperator(root, env, head_of_root, status);
		if (*status)
			return (*status);
	}
	else if (!ft_strncmp(root->node->content, "||", 3) && !root->node->is_op)
	{
		*status = execute_or_operatore(root, env, head_of_root, status);
		if (*status)
			return (*status);
	}
	return (0);
}
