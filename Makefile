CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIB_DIR = ./libft
BIN_NAME = test.out
SRCS = test.c
OBJS = $(SRCS:.c=.o)
LEAK_BIN = leak.out
LEAK_SRCS = test_leaks.c
LEAK_OBJS = $(SRCS:.c=.o)

all: test

test: $(BIN_NAME)
	./$(BIN_NAME)

$(BIN_NAME): $(SRCS) libft
	$(CC) $^ -o $@ -g -lbsd -L$(LIB_DIR) -lft

leak: $(BIN_LEAK)
	./$(BIN_LEAK)

$(BIN_LEAK): $(LEAK_OBJS) libft
	$(CC) $^ -o $@ -g -L$(LIB_DIR) -lft

libft:
	$(MAKE) -C $(LIB_DIR) bonus

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: test leak libft all clean fclean re
