/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:02:47 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/30 00:16:20 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/minishell.h"

int	g_lobal_sign_forherdoc = 0;

void	sigint(int signo)
{
	(void)signo;
	if (waitpid(-1, NULL, WNOHANG) != -1)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &g_original_terminos);
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
		if (g_lobal_sign_forherdoc == 0)
		{
			tcsetattr(STDIN_FILENO, TCSANOW, &g_original_terminos);
			write(1, "Quit: 3\n", 8);
		}
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

	env = malloc(sizeof(char *) * 5);
	if (!env)
		return (NULL);
	env[0] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	if (!env[0])
		return (NULL);
	env[1] = get_cwd();
	if (!env[1])
		return (NULL);
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

	((void)argc, (void)argv);
	if (init_minihsell_arg(&status_code, env))
		return (0);
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
