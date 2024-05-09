NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

SRCS = main.c pipex.c pipex_utils.c
OBJS = $(SRCS:.c=.o)
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
