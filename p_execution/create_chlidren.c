/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_chlidren.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:20:39 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/30 02:23:30 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	executing_command(t_tree *content, char **env)
{
	char	**cmd;
	char	*path;

	path = valid_path(content->node->content);
	if (!path)
	{
		write(2, "minishell: command not found\n", 29);
		exit(EXIT_NOTCOMMAND);
	}
	if (set_file_io(content))
	{
		perror("dup");
		exit(errno);
	}
	cmd = setup_command(content);
	if (!cmd)
		exit(errno);
	get_local_env_representation(NULL, &env);
	if (execve(path, cmd, env) == -1)
	{
		free_2d_arr((void **)env);
		perror("Execve");
		exit(errno);
	}
}

int	create_chdilren(t_tree *content, char **env, t_tree *head_of_root,
	int *last_status)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid == -1)
		return (perror("fork"), ft_memset(last_status, 1, 2), 1);
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (its_builtins(content))
		{
			status = execute_builtins(content, env, head_of_root);
			exit(status);
		}
		else
			executing_command(content, env);
	}
	if (content->fd != 0)
		ft_close(content->fd);
	if (content->out_fd != 1)
		ft_close(content->out_fd);
	manage_pid(pid, CAPTURED, NULL);
	return (0);
}
