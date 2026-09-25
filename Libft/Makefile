

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
