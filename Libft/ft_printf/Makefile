NAME	= libftprintf.a
CC		= cc
CFLAGS	= -Wall -Werror -Wextra
SRCS	= ft_print_utils.c ft_print_utils2.c ft_printf.c
OBJ		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus