/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:45:48 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/06 10:30:04 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void handle_error()
{
	perror("Error :");
}

char **find_pathenv(void)
{
	char *env;
	char **path_arr;

	env = getenv("PATH");
	if (!env)
	{
		handle_error();
		exit(errno);
	}
	path_arr = ft_split(env , ':');
	if (!path_arr)
	{
		free(env);
		return (NULL);
	}
	return (path_arr);
}

char *valid_path(char *cmd)
{
	char	**path;
	char 	*tmp;
	char	*path_cmd;
	int		index;

	index = 0;
	path = find_pathenv();
	while (path[index])
	{
		tmp = ft_strjoin(path[index], "/");
		path_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(path_cmd, F_OK | X_OK))
		{
			free_2d_arr((void**)path);
			return (path_cmd);
		}
		free(path_cmd);
		index++;
	}
	free_2d_arr((void**)path);
	return (NULL);
}

int	open_files(char *file_name, int level)
{
	int fd = -1;

	if (level == 1)
		fd = open(file_name, O_RDONLY);
	else if (level == 2)
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (level == 3)
		fd = open(file_name, O_RDONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		handle_error();
		return(-1);
	}
	return (fd);
}

void dup_iofile(int fd_in, int fd_out)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		handle_error();
		exit(errno);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		handle_error();
		exit(errno);
	}
	if (fd_in != 0)
		close(fd_in);
	if (fd_out != 1)
		close(fd_out);
}

int set_file_io(t_tree *content)
{
	int fd_in;
	int fd_out;

	if (content->input_file != NULL)
	{
		fd_in = open_files(content->input_file, 1);
		content->fd =  fd_in;
	}
	// else if (content->input_file == NULL)
	// 	fd_in = content->fd;
	if (content->output_file != NULL)
	{
		fd_out = open_files(content->output_file, 2);
		content->out_fd = fd_out;
	}
	// else if (content->output_file == NULL)
	// 	fd_out = content->out_fd;
	if (content->node->content)
	{
		dup_iofile(content->fd, content->out_fd);
		return (0);
	}
	return (1);
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
		exit(0);
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

void executing_command(t_tree *content, char **env)
{
	char **cmd;
	char *path;

	path = valid_path(content->node->content);
	if (!path)
		exit(0);
	if (set_file_io(content))
		exit(0);
	cmd = setup_command(content);
	if (!cmd)
		exit(0);
	if (execve(path, cmd, env) == -1)
	{
		perror("Error");
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
		manage_fds(content->fd, CAPTURE);
	if (content->out_fd != 1)
		manage_fds(content->out_fd, CAPTURE);
	manage_pid(pid, CAPTURED);
}
void set_back_io(int save_state)
{
	if (dup2(save_state, STDOUT_FILENO) == -1)
	{
		perror("Error");
		return ;
	}
}

int	ft_dup_parent(t_tree *root)
{
	int save_state;
	int fd;

	save_state = 1;
	if (root->output_file != NULL)
	{
		save_state = dup(STDOUT_FILENO);
		if (save_state == -1)
			return (-1);
		fd = open_files(root->output_file, 2);
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			handle_error();
			return (1);
		}
	}
	return (save_state);
}

void executing_tree(t_tree *root, char **env)
{
	int save_state;

	if (root->left == NULL && root->right == NULL)
	{
		create_chdilren(root, env);
		return ;
	}
	else if(!ft_strncmp(root->node->content, "&&", 3))
	{
		save_state = ft_dup_parent(root);
		if (save_state == -1)
			return ;
		executing_tree(root->left, env);
		waitpid(-1, NULL, 0);
		executing_tree(root->right, env);
		set_back_io(save_state);
	}
	else
	{
		executing_tree(root->left, env);
		executing_tree(root->right, env);
	}
}
