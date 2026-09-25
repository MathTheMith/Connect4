# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvachon <mvachon@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/09 14:35:29 by mvachon           #+#    #+#              #
#    Updated: 2024/11/13 15:17:00 by mvachon          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRC = ft_atoi.c \
      ft_isdigit.c \
      ft_memset.c \
      ft_strlen.c \
      ft_strncmp.c \
      ft_putendl_fd.c \

HEADER = libft.h
NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
