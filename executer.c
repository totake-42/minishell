/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:09:57 by totake            #+#    #+#             */
/*   Updated: 2025/12/10 13:52:33 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_multiple_commands(t_data *data)
{
	int	**pipes;

	pipes = cleate_all_pipes(data->cmd_count);
	fork_children(data->cmd, pipes, data);
	close_all_pipes(pipes, data->cmd_count);
	wait_all(data->cmd, data);
	free_all_pipes(pipes, data->cmd_count);
	return (0);
}

int	execute_single_builtin(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	if (setup_redirects(cmd->redirect))
	{
		data->last_status = 1;
		return (-1);
	};
	data->last_status = execute_builtin(cmd, data);
	return (0);
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

int	executer(t_data *data)
{
	data->cmd_count = count_commands(data->cmd);
	if (data->cmd_count == 1 && is_builtin(data->cmd->argv[0]))
	{
		if (execute_single_builtin(data) < 0)
		{
			safe_free((void **)&data->line);
			free_cmd_list(data->cmd);
			unlink_heredoc_files(data->cmd);
			return (-1);
		}
	}
	else if (execute_multiple_commands(data) < 0)
	{
		safe_free((void **)&data->line);
		free_cmd_list(data->cmd);
		unlink_heredoc_files(data->cmd);
		return (-1);
	}
	unlink_heredoc_files(data->cmd);
	return (0);
}
