# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/01 02:28:33 by totake            #+#    #+#              #
#    Updated: 2025/12/01 02:28:35 by totake           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

SRCS = main.c \
	ft_string.c \
	ft_memory.c \
	ft_io.c \
	ft_append.c \
	ft_free.c \
	ft_error.c \
	lexer.c \
	lexer_ctype.c \
	lexer_token_type.c \
	lexer_token_len.c \
	expand.c \
	expand_utils.c \
	debug.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Test target
test: test_lexer
	./test_lexer

test_lexer: test_lexer.c $(filter-out main.o, $(OBJS))
	$(CC) $(CFLAGS) -o test_lexer test_lexer.c $(filter-out main.o, $(OBJS)) $(LDFLAGS)

test_clean:
	rm -f test_lexer

.PHONY: all clean fclean re test test_clean
