# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/01 02:28:33 by totake            #+#    #+#              #
#    Updated: 2025/12/18 14:12:32 by totake           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
# CFLAGS = -Wall -Wextra -Werror -g
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = main.c \
	ft_append.c \
	ft_free1.c \
	ft_free2.c \
	ft_error.c \
	ft_mkstemp.c \
	lexer.c \
	lexer_ctype.c \
	lexer_token_type.c \
	lexer_token_len.c \
	lexer_check.c \
	expand.c \
	expand_utils.c \
	parser.c \
	parser_argv.c \
	parser_redirect.c \
	executer.c \
	executer_pipe.c \
	executer_builtin.c \
	executer_child1.c \
	executer_child2.c \
	executer_redirect.c \
	heredoc.c \
	heredoc_utils.c \
	signal1.c \
	signal2.c \
	builtin/echo.c \
	builtin/cd.c \
	builtin/cd_logic.c \
	builtin/cd_utils.c \
	builtin/pwd.c \
	builtin/export.c \
	builtin/export_deal.c \
	builtin/export_sort.c \
	builtin/unset.c \
	builtin/env.c \
	builtin/exit.c \
	builtin/option_check.c \
	builtin/builtin_utils.c \
	debug.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I. -c $< -o $@
# 	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# Test target
test: test_lexer
	./test_lexer

test_lexer: test_lexer.c $(filter-out main.o, $(OBJS))
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -o test_lexer test_lexer.c $(filter-out main.o, $(OBJS)) $(LIBFT) $(LDFLAGS)

test_clean:
	rm -f test_lexer

.PHONY: all clean fclean re test test_clean
