# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/23 15:42:36 by vduriez           #+#    #+#              #
#    Updated: 2021/11/29 02:51:48 by vduriez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = pipex

INCLUDES = pipex.h

FSANITIZE = -fsanitize=address

SRCS =			ft_split.c				\
				ft_strjoin.c			\
				ft_strnstr.c			\
				main.c

OBJ = $(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(INCLUDES) $(OBJ)
		$(CC) $(FLAGS) $(OBJ) -o $(NAME)

fsanitize:	$(FSANITIZE)

$(FSANITIZE):	$(INCLUDES) $(OBJ) $(BONUS_OBJ)
		$(CC) $(FLAGS) $(FSANITIZE) $(OBJ) -o $(NAME)
clean:
		rm -rf $(OBJ) $(BONUS_OBJ)

fclean: clean
		rm -rf $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY : all clean fclean re bonus
