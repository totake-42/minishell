/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:52:58 by totake            #+#    #+#             */
/*   Updated: 2025/12/08 18:02:34 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**envp_copy(char **envp)
{
	size_t	i;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_envp = (char **)safe_alloc(sizeof(char *) * (i + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			while (i-- > 0)
				safe_free((void **)&new_envp[i]);
			safe_free((void **)&new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

int	init_data(t_data *data, char **envp)
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

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	if (init_data(&data, envp))
	{
		perror("init_data failed");
		return (1);
	}
	set_readline_sig();
	while (1)
	{
		data.line = readline("minishell> ");
		check_readline_sig(&data);
		if (data.line == NULL)
		{
			printf("\nexit\n");
			break ;
		}
		if (data.line[0])
		{
			add_history(data.line);
			lexer(&data);
			// print_tokens(data.token); // For debugging
			parser(&data);
			// print_cmds(data.cmd); // For debugging
			if (heredoc_handler(&data) < 0)
				continue ;
			executer(&data);
		}
		safe_free((void **)&data.line);
		set_readline_sig();
	}
	return (data.last_status);
}
