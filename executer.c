/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:09:57 by totake            #+#    #+#             */
/*   Updated: 2025/12/07 19:48:13 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redirect_file(t_redirect *redirect)
{
	int	fd;

	fd = -1;
	if (redirect->type == R_INPUT)
	{
		fd = open(redirect->filename, O_RDONLY);
	}
	else if (redirect->type == R_OUTPUT)
	{
		fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	}
	else if (redirect->type == R_APPEND)
	{
		fd = open(redirect->filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
	}
	return (fd);
}

int	open_redirects_file(t_redirect *redirect)
{
	int	fd;

	while (redirect != NULL)
	{
		if (redirect->type == R_HEREDOC)
		{
			redirect = redirect->next;
			continue ;
		}
		fd = open_redirect_file(redirect);
		if (fd == -1)
			return (-1);
		if (redirect->type == R_INPUT)
		{
			if (dup2(fd, STDIN_FILENO) < 0)
				return (-1);
			close(fd);
		}
		else if (redirect->type == R_OUTPUT || redirect->type == R_APPEND)
		{
			if (dup2(fd, STDOUT_FILENO) < 0)
				return (-1);
			close(fd);
		}
		redirect = redirect->next;
	}
	return (0);
}

void	setup_redirects(t_redirect *redirect)
{
	if (open_redirects_file(redirect) == -1)
	{
		perror("redirect");
		exit(1);
	}
}

size_t	count_commands(t_cmd *cmd)
{
	size_t	count;

	count = 0;
	while (cmd != NULL)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	executer(t_data *data)
{
	data->cmd_count = count_commands(data->cmd);
	if (data->cmd_count == 1 && is_builtin(data->cmd->argv[0]))
		execute_single_builtin(data);
	else
		execute_multiple_commands(data);
	cleanup_heredocs(data->cmd);
}
