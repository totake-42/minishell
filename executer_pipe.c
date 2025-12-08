/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 22:30:00 by totake            #+#    #+#             */
/*   Updated: 2025/12/05 14:50:14 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**cleate_all_pipes(size_t cmd_count)
{
	int		**pipes;
	size_t	i;

	pipes = (int **)ft_calloc(cmd_count - 1, sizeof(int *));
	i = 0;
	while (i < cmd_count - 1)
	{
		pipes[i] = (int *)ft_calloc(2, sizeof(int));
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(1);
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

void	wait_and_cleanup(t_cmd *cmd, int **pipes, t_data *data)
{
	t_cmd	*current;
	int		status;
	int		last_status;
	size_t	i;

	close_all_pipes(pipes, data->cmd_count);
	current = cmd;
	last_status = 0;
	while (current != NULL)
	{
		waitpid(current->pid, &status, 0);
		last_status = status;
		current = current->next;
	}
	data->last_status = WEXITSTATUS(last_status);
	i = 0;
	while (i < data->cmd_count - 1)
	{
		safe_free((void **)&pipes[i]);
		i++;
	}
	safe_free((void **)&pipes);
}

void	execute_multiple_commands(t_data *data)
{
	int	**pipes;

	pipes = cleate_all_pipes(data->cmd_count);
	fork_children(data->cmd, pipes, data);
	wait_and_cleanup(data->cmd, pipes, data);
}
