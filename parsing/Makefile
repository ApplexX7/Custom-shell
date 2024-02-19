# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/15 11:53:36 by mohilali          #+#    #+#              #
#    Updated: 2024/02/16 15:49:41 by mohilali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c ft_split_tokens.c labling.c

OBJCT = ${SRC:.c=.o}
CC = cc
CFALGS = -Wall -Wextra -Werror
RM = rm -rf
NAME = mini

all : $(NAME)

$(NAME) : $(OBJCT)
	$(CC) -lreadline  $(OBJCT) -o $(NAME) ../Libft-42/Mandatory/libft.a

%.o : %.c
	$(CC) $(CFALGS) -c $< -o $@

clean : 
	$(RM) $(OBJCT)

fclean : clean
	$(RM) $(NAME)

re : fclean all