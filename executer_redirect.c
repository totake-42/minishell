/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:09:57 by totake            #+#    #+#             */
/*   Updated: 2025/12/10 16:46:17 by totake           ###   ########.fr       */
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

int	save_stdio_ofd(int *stdin_ofd, int *stdout_ofd)
{
	*stdin_ofd = dup(STDIN_FILENO);
	*stdout_ofd = dup(STDOUT_FILENO);
	if (*stdin_ofd == -1 || *stdout_ofd == -1)
	{
		if (*stdin_ofd != -1)
			close(*stdin_ofd);
		if (*stdout_ofd != -1)
			close(*stdout_ofd);
		return (-1);
	}
	return (0);
}

void	restore_stdio(int stdin_ofd, int stdout_ofd)
{
	if (dup2(stdin_ofd, STDIN_FILENO) < 0)
	{
		perror("fatal: dup2 restore stdin");
		exit(1);
	}
	if (dup2(stdout_ofd, STDOUT_FILENO) < 0)
	{
		perror("fatal: dup2 restore stdout");
		exit(1);
	}
	close(stdin_ofd);
	close(stdout_ofd);
}

int	apply_single_redirect(t_redirect *r)
{
	int	fd;
	int	target;

	fd = open_redirect_file(r);
	if (fd == -1)
		return (-1);
	if (r->type == R_INPUT)
		target = STDIN_FILENO;
	else
		target = STDOUT_FILENO;
	if (dup2(fd, target) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	apply_all_redirects(t_redirect *redirect)
{
	while (redirect != NULL)
	{
		if (apply_single_redirect(redirect) == -1)
			return (-1);
		redirect = redirect->next;
	}
	return (0);
}
