NAME	= pipex

SRC		= pipex.c ft_split.c utils.c utils2.c child.c

#BONUS_SRC	=

SRC_DIR	= srcs/

#BONUS_SRC_DIR	= srcs_bonus/

OBJ	= $(addprefix $(SRC_DIR), $(SRC:.c=.o))

#BONUS_OBJ	= $(addprefix $(BONUS_SRC_DIR), $(BONUS_SRC:.c=.o))

INC_DIR = includes

CC		= cc

CFLAGS	= -Wall -Werror -Wextra

%.o: %.c
	$(CC) $(CFLAGS) -I ./includes -c  $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

#bonus: $(BONUS_OBJ)
#	$(CC) $(CFLAGS) $(BONUS_OBJ) -fsanitize=address -g -o $(NAME)

clean:
	rm -f $(OBJ)
#	rm -f $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re