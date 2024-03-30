/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:24:05 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/30 00:35:10 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

char	**find_pathenv(void)
{
	char	*env;
	char	**path_arr;

	env = getenv("PATH");
	if (!env)
	{
		env = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		if (!env)
			exit(0);
	}
	path_arr = ft_split(env, ':');
	if (!path_arr)
	{
		free(env);
		return (NULL);
	}
	return (path_arr);
}

char	*ft_commands_path(char **path, char *cmd)
{
	int		index;
	char	*tmp;
	char	*path_cmd;

	index = 0;
	while (path[index])
	{
		tmp = ft_strjoin(path[index], "/");
		path_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(path_cmd, F_OK | X_OK))
		{
			return (path_cmd);
		}
		free(path_cmd);
		index++;
	}
	return (NULL);
}

char	*valid_path(char *cmd)
{
	char	**path;
	char	*path_cmd;

	path = find_pathenv();
	path_cmd = NULL;
	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd + 1, X_OK))
			return (cmd);
		write(2, "minishell: NOT a exetuble command\n",34);
		exit(EXIT_NOTEXECUTABLE);
	}
	else
		path_cmd = ft_commands_path(path, cmd);
	free_2d_arr((void **)path);
	return (path_cmd);
}
