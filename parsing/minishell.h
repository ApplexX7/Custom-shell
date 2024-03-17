/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:26:17 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/17 17:39:41 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define BUFFER_SIZE 42
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <stdio.h> // TODO: remove this
#include "readline/history.h"
#include "readline/readline.h"
#include "../Libft-42/libft.h"
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <termios.h>


#define EXIT_CODEPARSING 258
#define EXIT_CODECOMAND 127
#define EXIT_CODEFILE 1

typedef struct s_tree
{
    t_list *node;
    struct s_tree *left;
    struct s_tree *right;
    int fd;
    int out_fd;
    char *input_file;
    char *output_file;
    int open_mod;
} t_tree;

typedef enum fd_action {
	CAPTURE,
	CLOSE,
	CLOSE_ALL,
} t_fd_action;

typedef enum pid_action {
	CAPTURED,
	WAIT,
} t_pid_action;

// expand args
void push_to_front(t_list **source, t_list *dest);
void do_nothing(void *arg);
t_list *convert_arr_to_list(char **arr);
void append_list(t_list *source, t_list **dest, char op);
char *get_env_value(char *arg);
t_list *get_right_node(t_list *head ,t_list *node);
void lst_delete_node(t_list **lst, t_list *node);
int arr_len(char **arr);
int lst_add_env_arg(char *arg, t_list **dest);
//int lst_add_env_arg(t_list **dest, t_list *node, char *value);
int add_node(t_list **dest, t_list *node);
int expand_args(t_list **lst);


// split tokens
t_list 	*split_tokens(char *av);
char 	**ft_srtok(char *av);
char	**ft_split(char const *s, char c);
void    lable_list(t_list *lst);
void print_ouput(t_list *node);
void print_ouput_op(t_list *node);


// combine_list
int combine_list(t_list **lst);

//check syntax error
int check_syntax(t_list *lst);

// helpers
void lst_remove_node(t_list **lst, t_list *node);
int is_space(t_list *node);
int is_wildcard(t_list *node);
void del_spaces(t_list **lst);
int new_and_add(t_list **head, void *content, char is_op);
char **convert_list_to_arr(t_list *lst);
t_list *copy_lst(t_list *lst);
void free_2d_arr(void **arr);
int join_and_add(t_list **dest, t_list *start, t_list *end);
char *join_list(t_list *lst);
t_list *copy_lst(t_list *lst);
int is_open_parenth(t_list *node);
int is_close_parenth(t_list *node);
void swap(t_list *a, t_list *b);
void bubbleSort(t_list *start);
int min(int a, int b);
int max(int a, int b);

//labling priority
t_list *find_roottree(t_list **list);
void del_parentis(t_list **lst);
void labling_prio(t_list *list);

/*build tree*/
t_tree *build_tree(t_list *list);
void treeprint(t_tree *root, int level);
void freetree(t_tree **root);

/*handle redirections*/
int ft_open_herdocs(t_list *list);
char	*get_next_line(int fd);
int ft_open_redirections(t_list *lst);

// wildcard
int expand_wildcard();

// set_tree_io
t_list *check_combined_redirection(t_list *lst);
int is_redirect_op(t_list *lst);
int is_input_redirect(t_list *lst);
int is_output_redirect(t_list *lst);
int set_io(t_tree *node, t_list *start);
void remove_redirections(t_tree *node, t_list *start);
int tree_set_io(t_tree *node);
int is_herdoc(t_list *lst);

// remove parenthesis
void remove_parenthesis(t_list **lst);
void remove_inclosing_parenth(t_list *start, t_list *end, t_list **lst);
void set_end(t_list *lst, t_list **end);

// handle redirections bottom
int handle_redirections_bottom(t_tree *node);
void remove_redirectiosn2(t_tree *node);
int set_single_io(t_tree *node, t_list *pos);


// open_pipes
int tree_copy_output(char *output_file, int out_fd, t_tree *to);
int tree_copy_input(char *input_file, int fd, t_tree *to);
int open_pipes(t_tree *root);
void inheritance_bottom(t_tree *root);

//manage pids and fds and executing 
int	executing_tree(t_tree *root, char **env);
int	manage_fds(int fd, t_fd_action action);
int	manage_pid(int pid, t_pid_action action, int *last_status);
int ft_open(char *file, int mode, int perms);
int ft_close(int fd);

//executing part

void executing_command(t_tree *content, char **env);
void create_chdilren(t_tree *content, char **env);
char **find_pathenv(void);
char *valid_path(char *cmd);
int	open_files(char *file_name, int level);
void dup_iofile(int fd_in, int fd_out);
int set_file_io(t_tree *content);
int	ft_dup_parent(t_tree *root);
void set_back_io(int input, int output);
void handle_error();
char **setup_command(t_tree *content);
int is_andor(t_tree *root);
int check_operators(t_tree *root ,char **env);

// split_env_arg
int split_env_arg(t_list **lst);
int split_arg_node(t_list *node, t_list **dest);

// builtins

// echo
int ft_echo(t_tree *root);

// export
int ft_export(t_tree *root, char **env);
char *get_exported_arg_value(char *arg, t_list **local_lst, int free_bit);
int init_local_env(t_list **local_env, char **env);
int add_export_node(t_list *lst, t_list **local_env);
int search_and_add(t_list **local_env, char *key, char *value);
int is_valid_arg_name(char *start, char *end);
int check_export_syntax(char *content);
int print_export(t_list *lst, int fd);
int get_key_value(char *content, char **key, char **value, int *join);
int concat_and_add(char *key, char *value, t_list **local_env);
int export_add_key_value(t_list **dest, char *key, char *value);

//cd
int ft_cd(t_tree *root);

// env
int ft_env(t_tree *node, t_list **local_lst);

// builtins_helpers
int set_fd(int *set, t_tree *root);

// masking
int masking(t_list *start, t_list *end, t_list *dest);
void full_withzero(char **s);
void full_withone(char **s);
int there_is_expand(t_list *start, t_list *end);

// debug
void test_export(char **env);

#endif
