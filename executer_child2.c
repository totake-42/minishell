/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_child2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:26:29 by totake            #+#    #+#             */
/*   Updated: 2025/12/18 13:28:00 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_slash_target(char *name)
{
	if (access(name, F_OK) != 0)
	{
		errno = ENOENT;
		return (0);
	}
	if (access(name, X_OK) != 0)
	{
		errno = EACCES;
		return (0);
	}
	return (1);
}

char	*get_execve_path(char *name, t_data *data)
{
	char	*path;
	char	**paths;

	if (ft_strchr(name, '/'))
	{
		if (!check_slash_target(name))
			return (NULL);
		return (name);
	}
	path = get_env_value("PATH", data);
	if (path == NULL || *path == '\0')
	{
		safe_free((void **)&path);
		errno = ENOENT;
		return (NULL);
	}
	paths = ft_split(path, ':');
	safe_free((void **)&path);
	return (search_paths(paths, name));
}

static void	set_not_found_errno(int found)
{
	if (found)
		errno = EACCES;
	else
		errno = ENOENT;
}

char	*search_paths(char **paths, char *name)
{
	size_t	i;
	char	*full_path;
	char	*tmp;
	int		found;

	i = 0;
	found = 0;
	while (paths && paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, name);
		safe_free((void **)&tmp);
		if (access(full_path, F_OK) == 0)
			found = 1;
		if (access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		safe_free((void **)&full_path);
		i++;
	}
	free_split(paths);
	set_not_found_errno(found);
	return (NULL);
}

void	print_cmd_not_found(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
}
