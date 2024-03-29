/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:08:04 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/29 16:40:46 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	its_builtins(t_tree *root)
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
		return (1);
	if (!ft_strncmp(root->node->content, "pwd", 4))
		return (1);
	if (!ft_strncmp(root->node->content, "exit", 5))
		return (1);
	return (0);
}

int	execute_builtins(t_tree *root, char **env, t_tree *head_of_tree)
{
	if (!ft_strncmp(root->node->content, "echo", 5))
		return (ft_echo(root));
	if (!ft_strncmp(root->node->content, "export", 7))
		return (ft_export(root, env, 0));
	printf("fsfsfs\n");
	if (!ft_strncmp(root->node->content, "env", 4))
		return (ft_env(root, NULL));
	if (!ft_strncmp(root->node->content, "cd", 3))
		return (ft_cd(root));
	if (!ft_strncmp(root->node->content, "unset", 6))
		return (ft_unset(root, NULL));
	if (!ft_strncmp(root->node->content, "pwd", 4))
		return (ft_pwd(root));
	if (!ft_strncmp(root->node->content, "exit", 5))
		return (ft_exit(root, head_of_tree));
	return (0);
}
