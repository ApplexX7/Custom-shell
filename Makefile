# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/15 11:53:36 by mohilali          #+#    #+#              #
#    Updated: 2024/03/15 01:20:38 by ayait-el         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c parsing/ft_split_tokens.c parsing/labling.c parsing/debug.c parsing/new_expand_args.c parsing/check_syn.c parsing/combine_list.c parsing/helper.c \
	parsing/labling_priority.c parsing/build_tree.c parsing/open_redirections.c parsing/get_next_line.c parsing/helpers.c parsing/wildcard.c parsing/set_tree_io.c \
	parsing/remove_parenthesis.c parsing/handle_redirections_bottom.c parsing/open_pipes.c p_execution/execute_tree.c p_execution/garbege_collector.c \
	p_execution/change_state.c p_execution/create_chlidren.c p_execution/open_files.c p_execution/path.c parsing/split_env_args.c \
	builtins/env.c builtins/echo.c builtins/export.c builtins/builtins_helpers.c

OBJCT = ${SRC:.c=.o}
CC = cc
#TODO: remove -g
CFALGS = -Wall -Wextra -Werror -g
RM = rm -rf
NAME = mini
READLINEDIR  =  $(shell brew --prefix readline)

all : $(NAME)

$(NAME) : $(OBJCT)
	$(CC) -lreadline  $(OBJCT) -g -o $(NAME) Libft-42/libft.a -L$(READLINEDIR)/lib -lreadline

%.o : %.c
	$(CC) $(CFALGS) -c $< -o $@ -I$(READLINEDIR)/include
clean : 
	$(RM) $(OBJCT)

fclean : clean
	$(RM) $(NAME)

re : fclean all
