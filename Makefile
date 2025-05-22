NAME        = philo
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -O3 -g3
INCLUDES    = -I.

SRC         = main.c \
              src/init.c src/philo.c src/utils.c \
              utils/utils.c

OBJ         = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $(NAME)"
	$(CC) $(OBJ) -o $(NAME)

$(OBJ): %.o: %.c
	@echo "Compiling $<"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
