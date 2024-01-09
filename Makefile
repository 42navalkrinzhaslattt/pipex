NAME	= pipex

SRC		= pipex.c exit.c child.c parse.c

BONUS_SRC	=

SRC_DIR	= srcs/

BONUS_SRC_DIR	= srcs_bonus/

OBJ	= $(addprefix $(SRC_DIR), $(SRC:.c=.o))

BONUS_OBJ	= $(addprefix $(BONUS_SRC_DIR), $(BONUS_SRC:.c=.o))

INC_DIR = includes

LIBFT	= libft/libft.a

CC		= cc

CFLAGS	= -Wall -Werror -Wextra

MLX		= mlx_linux/libmlx_Linux.a

%.o: %.c
	$(CC) $(CFLAGS) -I ./includes -c  $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -Llibft -lft -fsanitize=address -g -o $(NAME)

bonus: $(LIBFT) $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -Llibft -lft -fsanitize=address -g -o $(NAME)

$(LIBFT):
	make -C libft all

clean:
	rm -f $(OBJ)
	rm -f $(BONUS_OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re:	fclean all

.PHONY: all clean fclean re