

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../Libft-42/libft.h"

void free_3d_arr(void **arr);
void push_to_front(t_list **source, t_list *dest);
void do_nothing(void *arg);
t_list *convert_arr_to_list(char **arr);
void append_list(t_list *source, t_list **dest);
char **convert_list_to_arr(t_list *lst);
char *get_env_value(char *arg, char **env);
t_list *get_right_node(t_list *head ,t_list *node);
void lst_delete_node(t_list **lst, t_list *node);
int arr_len(char **arr);
int lst_add_env_arg(char *arg, t_list **dest);
int add_node(t_list **dest, t_list *node);
t_list *expand_args(t_list **lst, char **env);

#endif
