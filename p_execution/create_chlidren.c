/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_chlidren.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:20:39 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/08 18:54:23 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void executing_command(t_tree *content, char **env)
{
	char **cmd;
	char *path;

	path = valid_path(content->node->content);
	if (!path)
	{
		handle_error();
		exit(EXIT_CODECOMAND);
	}
	if (set_file_io(content))
	{
		handle_error();
		exit(errno);
	}
	cmd = setup_command(content);
	if (!cmd)
		exit(errno);
	if (execve(path, cmd, env) == -1)
	{
		write(2, "Hello\n", 6);
		perror("Execve");
		exit(errno);
	}
}

void create_chdilren(t_tree *content, char **env)
{
	int pid;
	
	pid = fork();
	if (pid == -1)
		handle_error();
	else if (pid == 0)
	{
		executing_command(content, env);
	}
	if (content->fd != 0)
		close(content->fd);
	if (content->out_fd != 1)
		close(content->out_fd);
	manage_pid(pid, CAPTURED, NULL);
}
