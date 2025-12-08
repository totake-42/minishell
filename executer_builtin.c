/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 23:10:35 by totake            #+#    #+#             */
/*   Updated: 2025/12/04 23:10:36 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_cmd *cmd, t_data *data)
{
	if (ft_strncmp(cmd->argv[0], "echo", ft_strlen("echo")) == 0)
		return (builtin_echo(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "cd", ft_strlen("cd")) == 0)
		return (builtin_cd(cmd->argv, data));
	if (ft_strncmp(cmd->argv[0], "pwd", ft_strlen("pwd")) == 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd->argv[0], "export", ft_strlen("export")) == 0)
		return (builtin_export(cmd->argv, data));
	if (ft_strncmp(cmd->argv[0], "unset", ft_strlen("unset")) == 0)
		return (builtin_unset(cmd->argv, data));
	if (ft_strncmp(cmd->argv[0], "env", ft_strlen("env")) == 0)
		return (builtin_env(data));
	if (ft_strncmp(cmd->argv[0], "exit", ft_strlen("exit")) == 0)
		return (builtin_exit(cmd->argv, data));
	return (0);
}

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", ft_strlen("env")) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0)
		return (1);
	return (0);
}

void	execute_single_builtin(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	setup_redirects(cmd->redirect);
	data->last_status = execute_builtin(cmd, data);
}
