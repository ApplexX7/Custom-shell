# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/15 11:53:36 by mohilali          #+#    #+#              #
#    Updated: 2024/02/19 20:08:12 by ayait-el         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ../main.c ft_split_tokens.c labling.c debug.c expand_args.c combine_list.c

OBJCT = ${SRC:.c=.o}
CC = cc
#TODO: remove -g
CFALGS = -Wall -Wextra -Werror -g
RM = rm -rf
NAME = mini

all : $(NAME)

$(NAME) : $(OBJCT)
	$(CC) -lreadline  $(OBJCT) -o $(NAME) ../Libft-42/libft.a

%.o : %.c
	$(CC) $(CFALGS) -c $< -o $@

clean : 
	$(RM) $(OBJCT)

fclean : clean
	$(RM) $(NAME)

re : fclean all
