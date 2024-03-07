/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:26:17 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/07 23:22:29 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define BUFFER_SIZE 42
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <stdio.h> // TODO: remove this
#include <readline/history.h>
#include <readline/readline.h>
#include "../Libft-42/libft.h"
#include <dirent.h>
#include <errno.h>

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
char *get_env_value(char *arg, char **env);
t_list *get_right_node(t_list *head ,t_list *node);
void lst_delete_node(t_list **lst, t_list *node);
int arr_len(char **arr);
int lst_add_env_arg(char *arg, t_list **dest);
int add_node(t_list **dest, t_list *node);
int expand_args(t_list **lst, char **env);


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
int check_syn(t_list *list);

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

// split_env_arg
int split_env_arg(t_list **lst);
int split_arg_node(t_list *node, t_list **dest);

#endif
