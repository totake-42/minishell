/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:00:00 by totake            #+#    #+#             */
/*   Updated: 2025/12/07 20:26:12 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_heredocs(t_cmd *cmd)
{
	t_redirect	*r;

	while (cmd != NULL)
	{
		r = cmd->redirect;
		while (r != NULL)
		{
			if (r->type == R_INPUT && r->filename != NULL
				&& ft_strnstr(r->filename, "/tmp/minishell_heredoc",
					ft_strlen(r->filename)))
			{
				unlink(r->filename);
			}
			r = r->next;
		}
		cmd = cmd->next;
	}
}

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

static void	write_heredoc_line(int fd, char *line, int should_expand,
		t_data *data)
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
			break ;
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

int	fork_heredoc_child(int fd, t_redirect *redirect, t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		read_heredoc_content(redirect->filename, fd, redirect->should_expand,
			data);
	}
	waitpid(pid, &status, 0);
	data->last_status = WEXITSTATUS(status);
	if (WIFEXITED(status) && data->last_status == 130)
		return (-1);
	return (0);
}

int	handle_heredoc(t_redirect *redirect, t_data *data)
{
	int		fd;
	char	template_str[] = "/tmp/minishell_heredocXXXXXX";

	fd = create_heredoc_file(template_str);
	if (fd == -1)
		return (-1);
	if (fork_heredoc_child(fd, redirect, data) == -1)
	{
		close(fd);
		unlink(template_str);
		return (-1);
	}
	close(fd);
	safe_free((void **)&redirect->filename);
	redirect->filename = ft_strdup(template_str);
	redirect->type = R_INPUT;
	return (0);
}

int	handle_heredocs(t_cmd *cmd, t_data *data)
{
	t_redirect	*redirect;

	while (cmd != NULL)
	{
		redirect = cmd->redirect;
		while (redirect != NULL)
		{
			if (redirect->type == R_HEREDOC)
			{
				if (handle_heredoc(redirect, data) == -1)
					return (-1);
			}
			redirect = redirect->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
