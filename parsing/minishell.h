/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:26:17 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/19 14:06:43 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "../Libft-42/Mandatory/libft.h"


void 	split_tokens(char *av);
char 	**ft_srtok(char *av);
char	**ft_split(char const *s, char c);
void    lable_list(t_list *lst);
void print_ouput(t_list *node);
void print_ouput_op(t_list *node);

#endif