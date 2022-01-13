# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/23 15:42:36 by vduriez           #+#    #+#              #
#    Updated: 2022/01/11 22:37:05 by vduriez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = pipex

NAME_BONUS = pipex_bonus

INCLUDES = include/pipex.h

FSANITIZE = -fsanitize=address -fsanitize=undefined -g3

SRCS =			mandatory/ft_split.c			\
				mandatory/ft_strjoin.c			\
				mandatory/ft_strncmp.c			\
				mandatory/main.c

SRCS_BONUS =	bonus/ft_split.c			\
				bonus/ft_strjoin.c			\
				bonus/ft_strncmp.c			\
				bonus/main_bonus.c			\
				bonus/ft_norme.c

OBJ = $(SRCS:.c=.o)

OBJ_BONUS = $(SRCS_BONUS:.c=.o)

all:		$(NAME)

$(NAME):	$(INCLUDES) $(OBJ)
		$(CC) $(FLAGS) $(OBJ) -o $(NAME)

bonus:		$(NAME_BONUS)

$(NAME_BONUS):	$(INCLUDES) $(OBJ_BONUS)
		$(CC) $(FLAGS) $(OBJ_BONUS) -o $(NAME_BONUS)

fsanitize:	$(FSANITIZE)

$(FSANITIZE):	$(INCLUDES) $(OBJ) $(OBJ_BONUS)
		$(CC) $(FLAGS) $(FSANITIZE) $(OBJ) -o $(NAME)
clean:
		rm -rf $(OBJ) $(OBJ_BONUS)

fclean: clean
		rm -rf $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY : all clean fclean re bonus
