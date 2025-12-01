/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:30:31 by totake            #+#    #+#             */
/*   Updated: 2025/12/01 13:55:30 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h> //open()
# include <readline/history.h>
# include <readline/readline.h>
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
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
	T_END
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*str;
	struct s_token	*next;
}					t_token;

typedef enum e_redir_type
{
	R_INPUT,
	R_OUTPUT,
	R_APPEND,
	R_HEREDOC
}					t_redir_type;

typedef struct s_fd
{
	t_redir_type	type;
	char			*path;
	int				fd;
}					t_fd;

typedef struct s_cmd
{
	char			**argv;
	char			*path;
	pid_t			pid;
	t_fd			*infile_fd;
	t_fd			*outfile_fd;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_data
{
	char			*line;
	t_token			*token;
	char			**envp;
	t_cmd			*cmd;
	t_cmd			*cur_cmd;
	int				last_status;
}					t_data;

/* ===== ft_string.c ===== */
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strdup(const char *s);
char				*ft_strchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlen(const char *s);

/* ===== ft_memory.c ===== */
void				*xmalloc(size_t size);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);

/* ===== ft_io.c ===== */
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
int					ft_isalnum(int c);

/* ===== ft_append.c ===== */
char				*ft_charappend(char *str, char c, size_t *len);
char				*ft_strappend(char *str, char *append_str, size_t *len);

/* ===== ft_free.c ===== */
void				safe_free(void **ptr);
void				free_token_list(t_token *token);

/* ===== ft_error.c ===== */
void				exit_with_error(char *message, int exit_code);

/* ===== lexer.c ===== */
void				append_token(t_token **head, t_token *new_token);
void				skip_whitespace(char **line);
t_token				*create_token_node(char *ptr, size_t len, t_data *data);
t_token				*build_token_list(t_data *data);
void				lexer(t_data *data);

/* ===== lexer_ctype.c ===== */
int					is_whitespace(char c);
int					is_delimiter(char c);
int					is_quote(char c);
int					is_special_in_dquote(char c);

/* ===== lexer_token_type.c ===== */
t_token_type		detect_token_type(char *str);
t_token_type		detect_delimiter_type(char *str);

/* ===== lexer_token_len.c ===== */
size_t				count_quoted_len(char *str, char quote_char);
size_t				count_plain_len(char *str);
size_t				next_token_len(char *str);

/* ===== expand.c ===== */
char				*handle_single_quote(char *raw_str);
char				*handle_double_quote(char *raw_str, t_data *data);
char				*handle_plain_string(char *raw_str, t_data *data);
char				*expand_raw_str(char *raw_str, t_data *data);

/* ===== expand_utils.c ===== */
char				*get_env_value(char *key, t_data *data);
char				*extract_var_key(char *str);
char				*expand_dollar(char *str, size_t *i, t_data *data);
char				*expand_str(char *str, t_data *data);

/* ===== main.c ===== */
char				**envp_copy(char **envp);
int					init_data(t_data *data, char **envp);

/* ===== debug.c ===== */
void				print_tokens(t_token *token);

#endif
