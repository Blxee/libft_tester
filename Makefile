CC = cc
CFLAGS = -g
LIB_DIR = libft/
BIN_NAME = test.out
SRCS = test.c
OBJS = $(SRCS:.c=.o)
LEAK_BIN = leak.out
LEAK_SRCS = test_leaks.c
LEAK_OBJS = $(SRCS:.c=.o)

all: test

test: $(BIN_NAME)
	./$(BIN_NAME)

$(BIN_NAME): $(OBJS) libft
	$(CC) $(OBJS) -o $@ $(CFLAGS) -lbsd -L$(LIB_DIR) -lft

leak: $(BIN_LEAK)
	./$(BIN_LEAK)

$(BIN_LEAK): $(LEAK_OBJS) libft
	$(CC) $(LEAK_OBJS) -o $@ $(CFLAGS) -L$(LIB_DIR) -lft

libft:
	$(MAKE) -C $(LIB_DIR) bonus

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -f $(BIN_NAME) $(LEAK_BIN)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: test leak libft all clean fclean re
