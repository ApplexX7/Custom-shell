/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:26:17 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/14 20:17:01 by mohilali         ###   ########.fr       */
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

typedef struct s_cmd
{
	char *data;
	char *token;
	struct s_cmd *next;	
}   t_cmd;


void hanlde_unqoutes(char *av);
char **ft_srtok(char *av);
char	**ft_split(char const *s, char c);
void hanlde_unquatoes(char *av);

#endif