/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:26:17 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/22 18:26:50 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h> // TODO: remove this
#include <readline/history.h>
#include <readline/readline.h>
#include "../Libft-42/Mandatory/libft.h"
#include <dirent.h>

// expand args
void free_3d_arr(void **arr);
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
int new_and_add(t_list **head, void *content);
char **convert_list_to_arr(t_list *lst);
t_list *copy_lst(t_list *lst);


// wildcard
int expand_wildcard();

#endif
