/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_tmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:54:37 by totake            #+#    #+#             */
/*   Updated: 2025/12/02 21:16:16 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **argv)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	// -n オプションチェック
	if (argv[1] && ft_strncmp(argv[1], "-n", ft_strlen("-n")) == 0)
	{
		newline = 0;
		i = 2;
	}
	// 引数を出力
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

int	builtin_cd(char **argv, t_data *data)
{
	char	*path;
	char	cwd[4096];

	// char	*pwd;
	// パス決定（引数なし → HOME）
	if (argv[1] == NULL)
	{
		path = get_env_value("HOME", data);
		if (path == NULL || path[0] == '\0')
		{
			printf("cd: HOME not set\n");
			return (1);
		}
	}
	else
		path = argv[1];
	// ディレクトリ変更
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	// PWDを更新
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		// PWD環境変数を更新
		// setenv("PWD", cwd, 1) など
	}
	return (0);
}

int	builtin_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}

int	builtin_export(char **argv, t_data *data)
{
	char	*key;
	char	*value;
	int		i;

	(void)data;
	i = 1;
	while (argv[i])
	{
		// KEY=VALUE 形式を解析
		key = argv[i];
		value = ft_strchr(key, '=');
		if (value == NULL)
		{
			printf("export: %s: not a valid identifier\n", key);
			i++;
			continue ;
		}
		// 環境変数に追加
		// setenv(key, value + 1, 1) など
		i++;
	}
	return (0);
}

int	builtin_unset(char **argv, t_data *data)
{
	int	i;

	i = 1;
	(void)data;
	while (argv[i])
	{
		// 環境変数を削除
		// unsetenv(argv[i]) など
		i++;
	}
	return (0);
}

int	builtin_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		printf("%s\n", data->envp[i]);
		i++;
	}
	return (0);
}

int	builtin_exit(char **argv, t_data *data)
{
	int	exit_code;

	exit_code = data->last_status;
	// 引数がある場合、その値を終了コードとする
	if (argv[1] != NULL)
	{
		exit_code = ft_atoi(argv[1]);
	}
	printf("exit\n");
	exit(exit_code);
}
