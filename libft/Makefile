# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sp <marvin@42.fr>                          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 16:41:48 by sp                #+#    #+#              #
#    Updated: 2023/11/09 16:20:12 by sp               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SOURCES = \
	  ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	  ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	  ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	  ft_strrchr.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_strncmp.c \
	  ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	  ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	  ft_printf.c ft_putcsidu.c ft_putxxp.c get_next_line.c ft_atol.c
BSOURCES =\
	  ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstadd_back.c \
	  ft_lstlast.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJECTS = $(SOURCES:.c=.o)
BOBJECTS = $(BSOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) -r $@ $?

bonus: $(OBJECTS) $(BOBJECTS)
	$(AR) -r $(NAME) $?

%.o: %.c
	$(CC) -c $(CFLAGS) $?

clean:
	rm -f $(OBJECTS) $(BOBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
