/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 23:37:36 by totake            #+#    #+#             */
/*   Updated: 2025/12/10 11:08:52 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_heredoc_file(char *template)
{
	int	fd;

	fd = ft_mkstemp(template);
	if (fd < 0)
	{
		perror("ft_mkstemp");
		return (-1);
	}
	return (fd);
}

void	write_heredoc_line(int fd, char *line, int should_expand, t_data *data)
{
	char	*expanded_line;

	if (should_expand)
	{
		expanded_line = expand_str(line, data);
		if (expanded_line != NULL)
		{
			ft_putendl_fd(expanded_line, fd);
			safe_free((void **)&expanded_line);
		}
	}
	else
	{
		ft_putendl_fd(line, fd);
	}
}

int	read_heredoc_content(const char *delimiter, int fd, int should_expand,
		t_data *data)
{
	char	*line;
	int		delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);
			break ;
		}
		if (ft_strncmp(line, delimiter, delimiter_len) == 0
			&& line[delimiter_len] == '\0')
		{
			safe_free((void **)&line);
			break ;
		}
		write_heredoc_line(fd, line, should_expand, data);
		safe_free((void **)&line);
	}
	close(fd);
	exit(0);
}

// Example return -1 case:
// fork error
// Ctrl+C during heredoc input

int	wait_heredoc_child(pid_t pid, t_data *data)
{
	int	status;

	set_ignore_sig();
	waitpid(pid, &status, 0);
	set_readline_sig();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		data->last_status = 128 + SIGINT;
		return (-1);
	}
	else if (WIFEXITED(status))
	{
		data->last_status = WEXITSTATUS(status);
	}
	return (0);
}

int	fork_heredoc_child(int fd, t_redirect *redirect, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		data->last_status = 1;
		return (-1);
	}
	if (pid == 0)
	{
		set_heredoc_sig();
		read_heredoc_content(redirect->filename, fd, redirect->should_expand,
			data);
	}
	return (wait_heredoc_child(pid, data));
}
