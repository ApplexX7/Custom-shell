/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:21:18 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/26 21:57:15 by mohilali         ###   ########.fr       */
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
	if (!ft_strncmp(path_dir, ".", 2) || !ft_strncmp(path_dir, "", 2))
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
	int status = 0;

	if (!root || !root->node)
		return (1);
	current = root->node;
	if (!current->next)
	{
		
		path_dir = ft_strdup(getenv("HOME"));
		if (!path_dir)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			ft_memset(&status, EXIT_FILENOTEXIST, 2);
			return (status);
		}
	}
	else
		path_dir = ft_strdup(current->next->content);
	if (change_dir(path_dir))
	{
		ft_memset(&status, EXIT_FILENOTEXIST, 2);
		return (free(path_dir), status);
	}
	// ft_export
	free(path_dir);
	return (0);
}
