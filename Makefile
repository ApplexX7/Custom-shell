# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/15 11:53:36 by mohilali          #+#    #+#              #
#    Updated: 2024/03/29 19:44:10 by mohilali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = minishell_parts.c main.c parsing/ft_split_tokens.c parsing/labling.c parsing/debug.c parsing/new_expand_args.c parsing/check_syn.c parsing/combine_list.c parsing/helper.c \
	parsing/labling_priority.c parsing/build_tree.c parsing/open_redirections.c parsing/helpers.c parsing/wildcard.c parsing/set_tree_io.c \
	parsing/remove_parenthesis.c parsing/handle_redirections_bottom.c parsing/open_pipes.c p_execution/execute_tree.c p_execution/garbege_collector.c \
	p_execution/change_state.c p_execution/create_chlidren.c p_execution/open_files.c p_execution/path.c parsing/split_env_args.c \
	builtins/env.c builtins/echo.c builtins/export.c builtins/builtins_helpers.c parsing/mask.c builtins/cd.c parsing/inheritance.c parsing/lable_env_args.c\
	builtins/unset.c parsing/expand_forherdoc.c builtins/pwd.c builtins/ft_exit.c parsing/ft_split_tokens_helper.c parsing/expand_herdoc_helpers.c parsing/check_syn_helpers.c \
 	parsing/expand_args_helpers.c parsing/expand_args_helpers2.c parsing/combine_list_helpers.c parsing/set_tree_io_helpers.c parsing/wildcard_helpers.c parsing/wildcard_helpers2.c builtins/export_helpers.c \
	builtins/export_helpers2.c parsing/helpers_two.c parsing/helpers_tree.c parsing/helpers_five.c parsing/helpers_sex.c parsing/helpers_for.c \
	p_execution/execute_andor.c  p_execution/execute_builtins.c p_execution/back_to_prevstate.c p_execution/manage_fds.c \
	p_execution/change_state_helpers.c
	


OBJCT = ${SRC:.c=.o}
CC = cc
#TODO: remove -g
CFALGS =  -Wall -Wextra -Werror -g
RM = rm -rf
NAME = mini
READLINEDIR  =  $(shell brew --prefix readline)
LIBS = Libft-42/libft.a

define MAKE_LIB
	make $1 -C $2

endef

all : $(NAME)

$(NAME) : $(OBJCT) $(LIBS)
	$(CC) -lreadline  $(OBJCT) -o $(NAME) Libft-42/libft.a -L$(READLINEDIR)/lib -lreadline -g

%.o : %.c
	$(CC) $(CFALGS) -c $< -o $@ -I$(READLINEDIR)/include
clean : 
	$(RM) $(OBJCT)
	$(foreach lib,$(LIBS),$(call MAKE_LIB,clean,$(word 1,$(subst /, ,$(lib)))))

fclean : clean
	$(RM) $(NAME)
	$(RM) $(LIBS)

re : fclean all

%.a: force
	$(foreach lib,$(LIBS),$(call MAKE_LIB,bonus,$(word 1,$(subst /, ,$(lib)))))

force: ;
.PHONEY: all clean fclean re force
