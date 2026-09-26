

SRC = ft_atoi.c \
      ft_isdigit.c \
      ft_memset.c \
      ft_strlen.c \
      ft_strncmp.c \
      get_next_line.c \
      get_next_line_utils.c \
      ft_putendl_fd.c \
      ft_putnbr_fd.c \

HEADER = libft.h get_next_line.h
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
