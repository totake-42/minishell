/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:09:57 by totake            #+#    #+#             */
/*   Updated: 2025/12/10 14:14:53 by totake           ###   ########.fr       */
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
		fd = open_redirect_file(redirect);
		if (fd == -1)
			return (-1);
		if (redirect->type == R_INPUT)
		{
			if (dup2(fd, STDIN_FILENO) < 0)
			{
				close(fd);
				return (-1);
			}
			close(fd);
		}
		else if (redirect->type == R_OUTPUT || redirect->type == R_APPEND)
		{
			if (dup2(fd, STDOUT_FILENO) < 0)
			{
				close(fd);
				return (-1);
			}
			close(fd);
		}
		redirect = redirect->next;
	}
	return (0);
}

int	setup_redirects(t_redirect *redirect)
{
	int	old_stdin;
	int	old_stdout;

	old_stdin = dup(0);
	old_stdout = dup(1);
	if (old_stdin == -1 || old_stdout == -1)
	{
		perror("dup");
		if (old_stdin != -1)
			close(old_stdin);
		if (old_stdout != -1)
			close(old_stdout);
		return (-1);
	}
	if (open_redirects_file(redirect) == -1)
	{
		perror("redirect");
		dup2(old_stdin, 0);
		dup2(old_stdout, 1);
		close(old_stdin);
		close(old_stdout);
		return (-1);
	}
	close(old_stdin);
	close(old_stdout);
	return (0);
}
