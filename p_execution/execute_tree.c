/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:45:48 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/30 02:13:24 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

char	**setup_command(t_tree *content)
{
	char	**cmd;
	t_list	*current;
	int		index;
	int		len;

	len = ft_lstsize(content->node);
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

int	is_andor(t_tree *root)
{
	if (!ft_strncmp(root->node->content, "&&", 3) && !root->node->is_op)
		return (1);
	if (!ft_strncmp(root->node->content, "||", 3) && !root->node->is_op)
		return (1);
	return (0);
}

int	set_up_executions(t_tree *root)
{
	if (inheritance_bottom(root))
		return (1);
	if (expand_args(&root->node))
		return (1);
	if (expand_wildcard(&root->node))
		return (1);
	del_spaces(&root->node);
	return (0);
}

int	executing_tree(t_tree *root, char **env,
	t_tree *head_of_root, int *status_code)
{
	if (root->left == NULL && root->right == NULL)
	{
		if (set_up_executions(root))
			return (ft_memset(status_code, EXIT_FILENOTEXIST, 2), *status_code);
		if (!root->fbuiltins && its_builtins(root))
			return (execute_builtins(root, env, head_of_root));
		else if (create_chdilren(root, env, head_of_root, status_code))
			return (-1);
	}
	else if (is_andor(root))
		*status_code = check_operators(root, env, head_of_root, status_code);
	else
	{
		if (executing_tree(root->left, env, head_of_root, status_code) == -1)
			return (-1);
		if (executing_tree(root->right, env, head_of_root, status_code) == -1)
			return (-1);
	}
	return (*status_code);
}
