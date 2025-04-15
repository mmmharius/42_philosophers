NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC_DIR = src

SRCS = main.c \
	   $(SRC_DIR)/init.c \
	   $(SRC_DIR)/routine.c \
	   $(SRC_DIR)/utils.c \
	   $(SRC_DIR)/monitor.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
