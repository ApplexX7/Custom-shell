/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:02:47 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/11 18:52:24 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing/minishell.h"
#include <termios.h>

int signal_handler = 0;

t_tree *spown_tree(t_list *lst)
{
	t_tree *root;

	if (!lst)
		return (NULL);
	if (ft_open_herdocs(lst))
		return (NULL);
	root = build_tree(lst);
	if (!root)
		return (NULL);
	return (root);
}

t_tree *parsing_check(char *promt, char **env, int *status_code)
{
	t_list *lst;
	t_tree *root;

	if (!promt)
		return (NULL);
	lst = split_tokens(promt);
	if (!lst)
		return (NULL);
	lable_list(lst);
	if (split_env_arg(&lst))
		return (ft_lstclear(&lst, &free), NULL);
	if (expand_args(&lst, env))
		return (ft_lstclear(&lst, &free), NULL);
	*status_code = check_syntax(lst);
	if (*status_code != 0)
		return (ft_lstclear(&lst, &free), NULL);
	if (combine_list(&lst))
		return (ft_lstclear(&lst, &free), NULL);
	if (expand_wildcard(&lst))
		return (ft_lstclear(&lst, &free), NULL);
	labling_prio(lst);
	del_spaces(&lst);
	root = spown_tree(lst);
	if (!root)
		return (ft_lstclear(&lst, &free), NULL);
	return (root);
}

int executing_part(t_tree *root, int *status_code, char **env)
{
	int code;

    if (open_pipes(root))
		return (0);
	*status_code = executing_tree(root, env);
	code = manage_pid(0, WAIT, status_code);
	manage_fds(0, CLOSE_ALL);
	return (0);
}

void sigint(int signo)
{
	(void) signo;
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

void sigquit(int signo)
{
	(void) signo;
	if (waitpid(-1, NULL, WNOHANG) != -1)
	{
		// printf("\n");
		write(1, "QUIT: 3\n", 8);
	}
	rl_redisplay();
	return ;
}

int recept_signals(void)
{
	signal(SIGINT, &sigint);
	signal(SIGQUIT, &sigquit);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	char *promt;
	static int status_code;
	// struct termios term, old;
	t_tree *root;

	(void) argc;
	(void) argv;
	status_code = 0;
/*
	TODO : STILL SOME WORK ON IT
	tcgetattr(STDIN_FILENO, &old);
	term = old;
	term.c_cflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	// tcsetattr(STDIN_FILENO,TCSANOW,&old);
*/
	recept_signals();
	while (1)
	{
		promt = readline("minishell %% ");
		if (!promt)
		{
			printf("exiting from shell....\n");
			exit(0);
		}
		root = parsing_check(promt, env, &status_code);
		if (root)
		{
			status_code = executing_part(root, &status_code, env);
			freetree(&root);
		}
		add_history(promt);
		free(promt);
	}
}
