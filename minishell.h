/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:30:31 by totake            #+#    #+#             */
/*   Updated: 2025/11/29 15:39:52 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h> //fork(), execve(), pid_t
#include <stdlib.h> //malloc(), free()
#include <sys/wait.h> //waitpid()
#include <fcntl.h> //open()
#include <stdio.h> //perror()

typedef enum e_token_type
{
	T_WORD,
    T_PIPE,
    T_REDIR_IN,
    T_REDIR_OUT,
    T_APPEND,
    T_HEREDOC,
} t_token_type;

typedef struct s_token
{
	t_token_type type;
    char *str;
    struct s_token *next;
}	t_token;

typedef enum e_redir_type
{
	R_INPUT,
	R_OUTPUT,
	R_APPEND,
	R_HEREDOC
}						t_redir_type;

typedef struct s_fd {
	t_redir_type type;
    char *path;
    int   fd;
}   t_fd;

typedef struct s_cmd
{
	char **argv;
	char *path;
	pid_t pid;
	t_fd *infile_fd;
	t_fd *outfile_fd;
	struct s_cmd *next;
}         t_cmd;

typedef struct s_data
{
	char *line;
	t_token *token;
	char **envp;
	t_cmd *cmd;
	t_cmd *cur_cmd;
	int last_status;
} t_data;

#endif
