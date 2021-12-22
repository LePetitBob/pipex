# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/23 15:42:36 by vduriez           #+#    #+#              #
#    Updated: 2021/12/22 00:56:23 by vduriez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

FLAGS = -Wall -Wextra -Werror -g

NAME = pipex

NAME_BONUS = pipex_bonus

INCLUDES = include/pipex.h

FSANITIZE = -fsanitize=address

SRCS =			mandatory/ft_split.c			\
				mandatory/ft_strjoin.c			\
				mandatory/ft_strnstr.c			\
				mandatory/main.c

SRCS_BONUS =	bonus/ft_split.c			\
				bonus/ft_strjoin.c			\
				bonus/ft_strnstr.c			\
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
