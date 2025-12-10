/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 22:30:00 by totake            #+#    #+#             */
/*   Updated: 2025/12/11 00:08:44 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return (NULL) if ft_calloc overflow
int	**cleate_all_pipes(size_t cmd_count)
{
	int		**pipes;
	size_t	i;

	if (cmd_count < 2)
		return (NULL);
	pipes = (int **)ft_calloc(cmd_count - 1, sizeof(int *));
	if (pipes == NULL)
		return (NULL);
	i = 0;
	while (i < cmd_count - 1)
	{
		pipes[i] = (int *)ft_calloc(2, sizeof(int));
		if (pipe(pipes[i]) == -1)
		{
			free_all_pipes(pipes, i + 1);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	close_all_pipes(int **pipes, size_t cmd_count)
{
	size_t	i;

	if (pipes == NULL)
		return ;
	i = 0;
	while (i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	free_all_pipes(int **pipes, size_t cmd_count)
{
	size_t	i;

	if (pipes == NULL)
		return ;
	i = 0;
	while (i < cmd_count - 1)
	{
		safe_free((void **)&pipes[i]);
		i++;
	}
	safe_free((void **)&pipes);
}

int	status_from_signal(int status, int *sigint_flag)
{
	if (WTERMSIG(status) == SIGINT && !(*sigint_flag))
	{
		write(STDERR_FILENO, "\n", 1);
		*sigint_flag = 1;
	}
	return (128 + WTERMSIG(status));
}

void	wait_all(t_cmd *cmd, t_data *data)
{
	t_cmd	*current;
	int		status;
	int		sigint_flag;

	current = cmd;
	set_ignore_sig();
	sigint_flag = 0;
	while (current != NULL)
	{
		waitpid(current->pid, &status, 0);
		// error case if (pid < 0)
		if (WIFEXITED(status))
			data->last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->last_status = status_from_signal(status, &sigint_flag);
		if (current->next == NULL && WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
		current = current->next;
	}
}
