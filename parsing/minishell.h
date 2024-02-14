

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../Libft-42/libft.h"

// parsing quotes
int is_valid_token(char *token);
char *get_next_quote(char *str);
int count_char(char *str, char chr);
char *remove_quotes(char *str, char quote);
int add_new_to_list(void *content, t_list **lst);
int add_to_list(char *edges[2], int is_quoted, char quote, t_list **lst);
int set_start_end(int *start, int *end, char *str);
int add_tokens_to_list(int start, int end, t_list **lst, char *str);
int check_for_unclosed_quotes(char *command);
t_list *handle_queotes(char *command);

#endif
