/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:09:57 by totake            #+#    #+#             */
/*   Updated: 2025/12/09 15:10:42 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_multiple_commands(t_data *data)
{
	int	**pipes;

	pipes = cleate_all_pipes(data->cmd_count);
	fork_children(data->cmd, pipes, data);
	close_all_pipes(pipes, data->cmd_count);
	wait_all(data->cmd, data);
	free_all_pipes(pipes, data->cmd_count);
}

void	execute_single_builtin(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	setup_redirects(cmd->redirect);
	data->last_status = execute_builtin(cmd, data);
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
		execute_single_builtin(data);
	else
		execute_multiple_commands(data);
	cleanup_heredocs(data->cmd);
	return (0);
}
