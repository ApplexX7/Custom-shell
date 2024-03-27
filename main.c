/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:02:47 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/27 17:14:26 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/minishell.h"
#include <termios.h>

struct termios	original_terminos;

t_tree	*spown_tree(t_list *lst)
{
	t_tree	*root;

	if (!lst)
		return (NULL);
	if (ft_open_herdocs(lst))
		return (NULL);
	root = build_tree(lst);
	if (!root)
		return (NULL);
	return (root);
}

t_tree	*parsing_check(char *promt, char **env, int *status_code)
{
	t_list	*lst;
	t_tree	*root;

	(void)env;
	lst = split_tokens(promt);
	if (!lst)
		return (NULL);
	add_history(promt);
	lable_list(lst);
	if (split_env_arg(&lst))
		return (ft_lstclear(&lst, &free), NULL);
	if (check_syntax(lst, status_code))
		return (ft_lstclear(&lst, &free), NULL);
	lable_env_args(lst);
	if (combine_list(&lst))
		return (ft_lstclear(&lst, &free), NULL);
	labling_prio(lst);
	del_spaces(&lst);
	root = spown_tree(lst);
	if (!root)
		return (ft_lstclear(&lst, &free), NULL);
	return (root);
}

int	executing_part(t_tree *root, int *status_code, char **env)
{
	t_tree	*head_of_root;

	head_of_root = root;
	if (open_pipes(root))
		return (0);
	*status_code = executing_tree(root, env, head_of_root);
	manage_fds(0, CLOSE_ALL);
	manage_pid(0, WAIT, status_code);
	return (0);
}

void	sigint(int signo)
{
	(void)signo;
	if (waitpid(-1, NULL, WNOHANG) != -1)
	{
		write(1, "\n", 1);
		return ;
	}
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit(int signo)
{
	(void)signo;
	if (waitpid(-1, NULL, WNOHANG) != -1)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &original_terminos);
		return ;
	}
	rl_redisplay();
	return ;
}

int	recept_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, &sigint);
	signal(SIGQUIT, &sigquit);
	return (0);
}

char	**create_env(void)
{
	char	**env;
	char	*buffer;
	size_t	size;

	size = PATH_MAX;
	env = malloc(sizeof(char *) * 5);
	if (!env)
		return (NULL);
	env[0] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	if (!env[0])
		return (NULL);
	buffer = malloc(sizeof(char) * size);
	if (!buffer)
		return (NULL);
	if (!getcwd(buffer, size))
		return (NULL);
	env[1] = ft_strjoin("PWD=", buffer);
	if (!env[1])
		return (NULL);
	free(buffer);
	env[2] = ft_strdup("SHLVL=1");
	if (!env[2])
		return (NULL);
	env[3] = ft_strdup("_=/usr/bin/env");
	if (!env[3])
		return (NULL);
	env[4] = 0;
	return (env);
}

int	main(int argc, char **argv, char **env)
{
	char		*promt;
	static int	status_code = 0;
	t_tree		*root;

	(void)argc;
	(void)argv;
	get_env_value(NULL, &status_code);
	tcgetattr(STDIN_FILENO, &original_terminos);
	recept_signals();
	if (!env || !env[0])
	{
		env = create_env();
		if (!env)
			return (0);
		ft_export(NULL, env, 1);
		free_2d_arr((void **)env);
	}
	else
		ft_export(NULL, env, 1);
	while (1)
	{
		promt = readline("minishell2.5>$ ");
		if (!promt)
		{
			if (promt == NULL)
				printf("exit\n");
			get_exported_arg_value(NULL, NULL, 1);
			exit(0);
		}
		root = parsing_check(promt, env, &status_code);
		if (root)
		{
			executing_part(root, &status_code, env);
			freetree(&root);
		}
		free(promt);
	}
}
