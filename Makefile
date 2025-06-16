NAME        = philo
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -O3 -g3
INCLUDES    = -I.

SRC         = main.c \
              src/init.c \
              src/init_utils.c \
              src/philo.c \
              src/philo_actions.c \
              src/philo_monitor.c \
              src/utils.c \

OBJ         = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Building project..."
	@$(CC) $(OBJ) -o $(NAME) > /dev/null
	@echo "Done! Executable: ./$(NAME)"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ > /dev/null

clean:
	@echo "cleaning .o ..."
	@rm -f $(OBJ)

fclean: clean
	@echo "Removing executable..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
