/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:30:31 by totake            #+#    #+#             */
/*   Updated: 2025/12/08 13:42:26 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>  //errno
# include <fcntl.h>  //open()
# include <limits.h> //LONG_MAX, LONG_MIN
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>   //sigaction(), sigemptyset()
# include <stdbool.h>  //bool
# include <stddef.h>   //size_t
# include <stdio.h>    //perror()
# include <stdlib.h>   //malloc(), free()
# include <sys/wait.h> //waitpid()
# include <unistd.h>   //fork(), execve(), pid_t

typedef enum e_token_type
{
	T_INVALID,
	T_WORD,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*str;
	char				*raw_str;
	struct s_token		*next;
}						t_token;

typedef enum e_redirect_type
{
	R_INPUT,
	R_OUTPUT,
	R_APPEND,
	R_HEREDOC
}						t_redirect_type;

typedef struct s_redirect
{
	t_redirect_type		type;
	char				*filename;
	int					should_expand;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_cmd
{
	char				**argv;
	t_redirect			*redirect;
	pid_t				pid;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_data
{
	char				*line;
	t_token				*token;
	char				**envp;
	t_cmd				*cmd;
	size_t				cmd_count;
	t_cmd				*cur_cmd;
	int					last_status;
}						t_data;

/* ===== ft_append.c ===== */
char					*ft_charappend(char *str, char c, size_t *len);
char					*ft_strappend(char *str, char *append_str, size_t *len);

/* ===== ft_free.c ===== */
void					safe_free(void **ptr);
void					free_token_list(t_token *token);

/* ===== ft_error.c ===== */
void					exit_with_error(char *message, int exit_code);

/* ===== ft_mkstemp.c ===== */
int						ft_mkstemp(char *template);

/* ===== lexer.c ===== */
void					append_token(t_token **head, t_token *new_token);
void					skip_whitespace(char **line);
t_token					*create_token_node(char *ptr, size_t len, t_data *data);
t_token					*build_token_list(t_data *data);
void					lexer(t_data *data);

/* ===== lexer_ctype.c ===== */
int						is_whitespace(char c);
int						is_delimiter(char c);
int						is_quote(char c);
int						is_special_in_dquote(char c);

/* ===== lexer_token_type.c ===== */
t_token_type			detect_token_type(char *str);
t_token_type			detect_delimiter_type(char *str);

/* ===== lexer_token_len.c ===== */
size_t					count_quoted_len(char *str, char quote_char);
size_t					count_plain_len(char *str);
size_t					next_token_len(char *str);

/* ===== expand.c ===== */
char					*handle_single_quote(char *raw_str);
char					*handle_double_quote(char *raw_str, t_data *data);
char					*handle_plain_string(char *raw_str, t_data *data);
char					*expand_raw_str(char *raw_str, t_data *data);

/* ===== expand_utils.c ===== */
char					*get_env_value(char *key, t_data *data);
char					*extract_var_key(char *str);
char					*expand_dollar(char *str, size_t *i, t_data *data);
char					*expand_str(char *str, t_data *data);

/* ===== main.c ===== */
char					**envp_copy(char **envp);
int						init_data(t_data *data, char **envp);

/* ===== debug.c ===== */
void					print_tokens(t_token *token);
void					print_cmds(t_cmd *cmd);

/* ===== parser.c ===== */
t_cmd					*create_cmd_node(t_token **token_ptr);
t_cmd					*build_cmd_list(t_data *data);
void					parser(t_data *data);

/* ===== parser_argv.c ===== */
void					append_arg(char ***argv, char *arg);
char					**build_argv(t_token **token_ptr);

/* ===== parser_redirect.c ===== */
int						is_redirect(t_token_type type);
void					append_redirect(t_redirect **head,
							t_redirect *new_redirect);
t_redirect_type			token_type_to_redirect_type(t_token_type type);
t_redirect				*create_redirect_node(t_token **token_ptr);
t_redirect				*build_redirects(t_token **token_ptr);
void					append_cmd(t_cmd **head, t_cmd *new_cmd);

/* ===== executer.c ===== */
void					setup_redirects(t_redirect *redirect);
size_t					count_commands(t_cmd *cmd);
void					executer(t_data *data);

/* ===== executer_pipe.c ===== */
int						**cleate_all_pipes(size_t cmd_count);
void					close_all_pipes(int **pipes, size_t cmd_count);
void					execute_multiple_commands(t_data *data);

/* ===== executer_child.c ===== */
char					*get_execve_path(char *name, t_data *data);
char					*search_paths(char **paths, char *name);
void					execute_child(t_cmd *cmd, t_data *data);
void					connect_pipefd_stdfd(t_data *data, int **pipes,
							size_t cmd_index);
void					fork_children(t_cmd *cmd, int **pipes, t_data *data);

/* ===== executer_heredoc.c ===== */
void					cleanup_heredocs(t_cmd *cmd);
int						handle_heredocs(t_cmd *cmd, t_data *data);

/* ===== executer_builtin.c ===== */
int						execute_builtin(t_cmd *cmd, t_data *data);
int						is_builtin(char *cmd);
void					execute_single_builtin(t_data *data);

/* ===== executer_builtin.c ===== */
int						set_signals(void);

/* ===== builtin_tmp.c ===== */
int						builtin_echo(char **argv);
int						builtin_cd(char **argv, t_data *data);
int						builtin_pwd(void);
int						builtin_export(char **argv, t_data *data);
int						builtin_unset(char **argv, t_data *data);
int						builtin_env(t_data *data);
int						builtin_exit(char **argv, t_data *data);

#endif
