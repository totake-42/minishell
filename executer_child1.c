/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_child1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:24:44 by totake            #+#    #+#             */
/*   Updated: 2025/12/18 13:39:11 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_env_path_set(t_data *data)
{
	char	*val;
	int		ret;

	val = get_env_value("PATH", data);
	ret = (val != NULL && val[0] != '\0');
	safe_free((void **)&val);
	return (ret);
}

void	execute_child(t_cmd *cmd, t_data *data)
{
	char	*path;

	if (!cmd->argv || !cmd->argv[0])
		exit(data->last_status);
	if (is_builtin(cmd->argv[0]))
		exit(execute_builtin(cmd, data));
	path = get_execve_path(cmd->argv[0], data);
	if (path == NULL)
	{
		write(2, "minishell: ", 11);
		if (!ft_strchr(cmd->argv[0], '/') && is_env_path_set(data)
			&& errno == ENOENT)
		{
			print_cmd_not_found(cmd->argv[0]);
			exit(127);
		}
		perror(cmd->argv[0]);
		if (errno == ENOENT)
			exit(127);
		exit(126);
	}
	execve(path, cmd->argv, data->envp);
	perror(cmd->argv[0]);
	exit(126);
}

void	child_connect_pipefd_stdfd(t_data *data, int **pipes, size_t cmd_index)
{
	if (pipes == NULL)
		return ;
	if (cmd_index > 0)
	{
		if (dup2(pipes[cmd_index - 1][0], STDIN_FILENO) < 0)
		{
			perror("dup2");
			exit(1);
		}
	}
	if (cmd_index < data->cmd_count - 1)
	{
		if (dup2(pipes[cmd_index][1], STDOUT_FILENO) < 0)
		{
			perror("dup2");
			exit(1);
		}
	}
}

void	setup_child_io(t_data *data, int **pipes, size_t i)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &data->termios_p) < 0)
	{
		perror("tcsetattr");
		exit(1);
	}
	set_child_sig();
	child_connect_pipefd_stdfd(data, pipes, i);
	close_all_pipes(pipes, data->cmd_count);
	if (apply_all_redirects(data->cur_cmd->redirect) < 0)
	{
		perror("redirect");
		exit(1);
	}
}

int	fork_children(t_cmd *cmd, int **pipes, t_data *data)
{
	size_t	i;

	i = 0;
	while (cmd != NULL)
	{
		cmd->pid = fork();
		if (cmd->pid < 0)
			return (-1);
		cmd->is_in_child = 1;
		data->cur_cmd = cmd;
		if (cmd->pid == 0)
		{
			setup_child_io(data, pipes, i);
			execute_child(cmd, data);
		}
		cmd = cmd->next;
		i++;
	}
	return (0);
}
