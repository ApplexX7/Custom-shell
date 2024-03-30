/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:26:17 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/29 23:58:45 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER_SIZE 42
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>
# include <stdio.h>
# include "readline/history.h"
# include "readline/readline.h"
# include "../Libft-42/libft.h"
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h>
# include <termios.h>

struct termios		g_original_terminos;

// exit status
# define EXIT_CODEPARSING 258
# define EXIT_NOTCOMMAND 127
# define EXIT_NOTEXECUTABLE 126
# define EXIT_FILENOTEXIST 1
# define EXIT_ABOVETYPE 255

typedef struct s_tree
{
	t_list			*node;
	struct s_tree	*left;
	struct s_tree	*right;
	int				fbuiltins;
	int				fd;
	int				out_fd;
	char			*input_file;
	char			*output_file;
	int				open_mod;
	t_list			*input_files;
	t_list			*output_files;
}					t_tree;

typedef enum fd_action
{
	CAPTURE,
	CLOSE,
	CLOSE_ALL,
}					t_fd_action;

typedef enum pid_action
{
	CAPTURED,
	WAIT,
}					t_pid_action;

// minihsell_parts
int					init_minihsell_arg(int *status_code, char **env);
char				*get_cwd(void);
t_tree				*parsing_check(char *promt, char **env, int *status_code);
t_tree				*spown_tree(t_list *lst);
int					executing_part(t_tree *root, int *status_code, char **env);
char				**create_env(void);
int					recept_signals(void);
void				sigquit(int signo);

// expand herdoc args
int					expand_herdoc(t_list **lst);
void				lst_delete_node(t_list **lst, t_list *node);
int					addback_node(t_list **dest, t_list *node);
int					add_env_args(char *arg, t_list **dest);
t_list				*convert_to_list(char **arr);
void				push_to_front(t_list **source, t_list *dest);

// expand args
void				push_to_front(t_list **source, t_list *dest);
void				append_list(t_list *source, t_list **dest, char op);
t_list				*get_right_node(t_list *head, t_list *node);
void				lst_delete_node(t_list **lst, t_list *node);
int					arr_size(char **arr);
// int lst_add_env_arg(t_list **dest, t_list *node, char *value);
int					expand_args(t_list **lst);

// expand helpers
int					join_values(char **arr, char **dest);
int					join_before(t_list *before, t_list **lst, t_list *current);
int					join_after(t_list *after, t_list **lst, t_list *current);
int					lst_add_env_arg(char *arg, t_list **dest);
int					get_empty_str_arr(char ***dest);

// expand helpers 2
int					set_ones_arr(char *str, char *mask, char ***ones);
int					set_zeros_arr(char *str, char *mask, char ***zeros);
int					fil_split_arr(t_list **splited, char **zeros, char **ones,
						char *mask);
t_list				*get_splited_list(char *str, char *mask);
int					handle_empty_string_case(char **value, t_list *node);

// split tokens
t_list				*split_tokens(char *av);
void				lable_list(t_list *lst);
int					ft_isnotdouble(int c);
int					ft_isspecial(int c);
int					ft_issspace(int c);
int					ft_tokencharcters(char *av, t_list **head, int *index);
int					ft_normalcharacters(char *av, t_list **head, int *index);
int					add_tolist(char *av, t_list **head, int index, int start);
void				print_ouput(t_list *node);
void				print_ouput_op(t_list *node);
t_list				*skip_spaces(t_list *start);
// combine_list
int					combine_list(t_list **lst);

// combine_list helpers
int					is_useless_token(t_list *node);
int					handle_consecutive_quotes(t_list *node);
void				del_useless_tokens(t_list **lst);
int					is_literal(t_list *node);

// check syntax error
int					check_syntax(t_list *lst, int *status_code);
void				status_code_of_syntax_error(int *status_code);
int					ft_redirectionop(t_list *current);
int					ft_special_operators(t_list *current);
int					check_opsyntax(t_list *lst);
int					ft_handle_parentiserror(t_list *lst);
int					handle_oppositions(t_list *lst);
int					closed_qpsayntax(t_list *lst);
int					valid_syntax(t_list *lst);
int					valid_parentis(t_list *lst);
void				syntax_error_handling(t_list *copy);
void				syntax_error_handling(t_list *copy);

// helpers
void				lst_remove_node(t_list **lst, t_list *node);
int					is_space(t_list *node);
int					is_wildcard(t_list *node);
void				del_spaces(t_list **lst);
int					new_and_add(t_list **head, void *content, char is_op);
char				**convert_list_to_arr(t_list *lst);
t_list				*copy_lst(t_list *lst);
void				free_2d_arr(void **arr);
int					join_and_add(t_list **dest, t_list *start, t_list *end);
char				*join_list(t_list *lst);
t_list				*copy_lst(t_list *lst);
int					is_open_parenth(t_list *node);
int					is_close_parenth(t_list *node);
void				swap(t_list *a, t_list *b);
void				bubbleSort(t_list *start);
int					min(int a, int b);
int					max(int a, int b);
int					arr_len(char **arr);
int					handle_ambiguous_redirection(t_list *file);
void				appendto_list(t_list *source, t_list **dest);
int					add_node(t_list **dest, t_list *node);
int					get_env_value(char *arg, int *status, char **dest);
t_list				*convert_arr_to_list(char **arr);
void				do_nothing(void *arg);
int					ft_lstjoin(t_list *lst, char **dest);
int					get_local_env_representation(t_list **local_env,
						char ***dest);
t_list				*skip_spaces(t_list *start);

// labling priority
t_list				*find_roottree(t_list **list);
void				del_parentis(t_list **lst);
void				labling_prio(t_list *list);

/*build tree*/
void				inheritance_builting(t_tree *root, int fbuiltins);
t_tree				*build_tree(t_list *list);
t_tree				*insert_tree(t_list *list, t_tree **root);
void				treeprint(t_tree *root, int level);
void				freetree(t_tree **root);
int					is_pipe(t_list *lst);

/*handle redirections*/
int					ft_open_herdocs(t_list *list);
char				*get_next_line(int fd);
int					ft_open_redirections(t_list *lst);

// wildcard
int					expand_wildcard(t_list **lst);

// wildcard helpers
t_list				*get_current_files(void);
t_list				*lst_copy_portion(t_list *start, t_list *end);
int					is_matched(char *str, t_list *wildcard, int open_end,
						int open_start);
void				remove_points_dir(t_list *start, t_list **lst,
						int *matched);
int					get_matched_list(t_list *start, t_list *end, t_list **dest);

// wildcard helpers 2
int					split_by_star(t_list **lst);
void				set_ends(int *open_end, int *open_start, t_list *lst);
int					add_if_nomatch(t_list **dest, t_list *start, t_list *end,
						int matched);
int					add_if_matched(t_list **dest, t_list *portion, int ends[2],
						int *matched);
int					split_and_add(t_list *tmp, t_list **dest);

// set_tree_io
int					set_io(t_tree *node, t_list *start, t_list **input_files,
						t_list **output_files);
int					tree_set_io(t_tree *node);
int					is_herdoc(t_list *lst);

// set_tree_io helpers
t_list				*check_combined_redirection(t_list *lst);
int					is_redirect_op(t_list *lst);
int					is_input_redirect(t_list *lst);
int					is_output_redirect(t_list *lst);

// set_tree_io helpers 2
void	remove_redirections(t_tree *node, t_list *start);
int	is_and_or_or(t_list *node);

// remove parenthesis
void				remove_parenthesis(t_list **lst);
void				remove_inclosing_parenth(t_list *start, t_list *end,
						t_list **lst);
void				set_end(t_list *lst, t_list **end);

// handle redirections bottom
int					handle_redirections_bottom(t_tree *node);
void				remove_redirectiosn2(t_tree *node);
int					set_single_io(t_tree *node, t_list *pos);

// open_pipes
int					tree_copy_output(char *output_file, int out_fd, t_tree *to);
int					tree_copy_input(char *input_file, int fd, t_tree *to);
int					open_pipes(t_tree *root);
int					inheritance_bottom(t_tree *root);

// manage pids and fds and executing
int					executing_tree(t_tree *root, char **env,
						t_tree *head_of_root, int *status);
int					manage_pid(int pid, t_pid_action action, int *last_status);
int					ft_open(char *file, int mode, int perms);
int					ft_close(int fd);

// manage_fds
int					manage_fds(int fd, t_fd_action action);

// executing part

void				executing_command(t_tree *content, char **env);
int					create_chdilren(t_tree *content, char **env,
						t_tree *head_of_root);
char				**find_pathenv(void);
char				*valid_path(char *cmd);
int					open_files(char *file_name, int level);
void				dup_iofile(int fd_in, int fd_out);
int					set_file_io(t_tree *content);
int					ft_dup_parent(t_tree *root);
void				set_back_io(int input, int output);
char				**setup_command(t_tree *content);
int					is_andor(t_tree *root);
int					check_operators(t_tree *root, char **env,
						t_tree *head_of_root, int *status);
int					its_builtins(t_tree *root);
int					execute_builtins(t_tree *root, char **env,
						t_tree *head_of_root);

// executing && || op
int					execute_andoperator(t_tree *root, char **env,
						t_tree *head_of_root, int *status);
int					execute_or_operatore(t_tree *root, char **env,
						t_tree *head_of_root, int *status);
int					its_builtins(t_tree *root);
int					execute_builtins(t_tree *root, char **env,
						t_tree *head_of_tree);

// dup states
void				set_back_io(int input, int output);
int					ouput_files_open(t_tree *root, t_list *current, int fd_out);
int					input_files(t_tree *node);
int					output_files(t_tree *root);

// split_env_arg
int					split_env_arg(t_list **lst);
int					split_arg_node(t_list *node, t_list **dest);

// lable_env_args
void				lable_env_args(t_list *lst);
int					dup_output(int fd_out);
int					dup_input(int fd_in);

// builtins

// pwd
int					ft_pwd(t_tree *root);

// echo
int					ft_echo(t_tree *root);

// export
int					ft_export(t_tree *root, char **env, int init);
int					search_and_add(t_list **local_env, char *key, char *value);
int					check_export_syntax(char *content);
int					concat_and_add(char *key, char *value, t_list **local_env);

// export helpers
int					add_env_arg(char *key, char *value, t_list **env);
char				*get_exported_arg_value(char *arg, t_list **local_lst,
						int free_bit);
int					add_export_node(t_list *lst, t_list **local_env);
int					is_valid_arg_name(char *start, char *end);
int					get_key_value(char *content, char **key, char **value,
						int *join);

// export helpers 2
int					init_local_env(t_list **local_env, char **env);
int					print_export(t_list *lst, int fd);
int					export_add_key_value(t_list **dest, char *key, char *value);
int					init_envs(t_list **local_env, char **env);

// exit
int					ft_exit(t_tree *node, t_tree *root_of_tree);

// cd
int					ft_cd(t_tree *root);

// env
int					ft_env(t_tree *node, t_list **local_lst);

// unset
int					ft_unset(t_tree *tree, t_list **local_env);

// builtins_helpers
int					set_fd(int *set, t_tree *root);
int					ft_putnstr_fd(char *str, int fd, int size);

// masking
int					masking(t_list *start, t_list *end, t_list *dest);
void				full_withzero(char **s);
void				full_withone(char **s);
int					there_is_expand(t_list *start, t_list *end);

// handle_ambiguous_redirection_bottom
int	handle_ambiguous_redirection_bottom(t_list *file);

// join_mask
int	join_mask(t_list *start, t_list *end, t_list *dest);

// debug
void				test_export(char **env);

#endif
