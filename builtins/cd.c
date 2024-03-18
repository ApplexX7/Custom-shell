/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:21:18 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/18 17:04:25 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int execute_cd(char *pathname)
{
	if (chdir(pathname))
		return (1);
	return (0);
}

int change_dir(char *path_dir)
{
	struct stat info;
	char *tmp;

	tmp = path_dir;
	if (!path_dir)
		return (write(2, "Malloc failed!!\n", 16),1);
	if (!ft_strncmp(path_dir, ".", 2))
		execute_cd(path_dir);
	else if (!ft_strncmp(path_dir, "..", 3))
		execute_cd(path_dir);
	else
	{
		if (stat(path_dir, &info))
		{
			write(2,"minishell: cd: Not a directory\n",31);
			return (1);
		}
		if (execute_cd(path_dir))
			return (1);
	}
	return (0);
}

int ft_cd(t_tree *root)
{
	t_list *current;
	char *path_dir;

	if (!root || !root->node)
		return (1);
	current = root->node;
	if (!current->next || !ft_strncmp(current->next->content, "~", 2))
	{
		
		path_dir = ft_strdup(getenv("HOME"));
		if (!path_dir)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (EXIT_CODEFILE);
		}
	}
	else
		path_dir = ft_strdup(current->next->content);
	if (change_dir(path_dir))
		return (free(path_dir) ,EXIT_CODEFILE);
	free(path_dir);
	return (0);
}
