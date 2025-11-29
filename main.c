/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:52:58 by totake            #+#    #+#             */
/*   Updated: 2025/11/29 15:39:56 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void safe_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

char **envp_copy(char **envp)
{
	int i;
	char **new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			// Free previously allocated strings
			while (i-- > 0)
				safe_free(new_envp[i]);
			safe_free(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

int init_data(t_data *data, char **envp)
{
	data->line = NULL;
	data->token = NULL;
	data->envp = envp_copy(envp);
	data->cmd = NULL;
	data->cur_cmd = NULL;
	data->last_status = 0;

	if (!data->envp)
		return (-1);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_data data;

	(void)argc;
	(void)argv;
	if (init_data(&data, envp))
	{
		perror("init_data failed");
		return (1);
	}

	while (1)
	{
		char *line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (line[0])
			add_history(line);
	}
	return (0);
}
