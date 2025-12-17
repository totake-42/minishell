/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:12:07 by totake            #+#    #+#             */
/*   Updated: 2025/12/17 18:07:52 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_execve_path(char *name, t_data *data)
{
	char	*path;
	char	**paths;

	if (ft_strchr(name, '/'))
		return (ft_strdup(name));
	path = get_env_value("PATH", data);
	if (path == NULL)
		path = ft_strdup("./");
	paths = ft_split(path, ':');
	return (search_paths(paths, name));
}

char	*search_paths(char **paths, char *name)
{
	size_t	i;
	char	*full_path;
	char	*tmp;

	i = 0;
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, name);
		safe_free((void **)&tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		safe_free((void **)&full_path);
		i++;
	}
	return (NULL);
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
		write(2, "minishell: ", 12);
		write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(2, ": command not found\n", 20);
		// ft_putendl_fd("minishell: command not found", 2);
		if (errno == ENOENT)
			exit(127);
		else
			exit(126);
	}
	execve(path, cmd->argv, data->envp);
	perror(cmd->argv[0]);
	exit(126);
}

void	child_connect_pipefd_stdfd(t_data *data, int **pipes, size_t cmd_index)
{
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
		if (cmd->pid == 0)
		{
			// tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
			set_child_sig();
			child_connect_pipefd_stdfd(data, pipes, i);
			close_all_pipes(pipes, data->cmd_count);
			if (apply_all_redirects(cmd->redirect) < 0)
			{
				perror("redirect");
				exit(1);
			}
			execute_child(cmd, data);
		}
		cmd = cmd->next;
		i++;
	}
	return (0);
}
