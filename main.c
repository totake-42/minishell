/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:52:58 by totake            #+#    #+#             */
/*   Updated: 2025/12/09 16:27:36 by totake           ###   ########.fr       */
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
	if (!data->envp)
		return (-1);
	data->cmd = NULL;
	data->cur_cmd = NULL;
	data->last_status = 0;
	return (0);
}

void	prompt_loop(t_data *data)
{
	while (1)
	{
		set_readline_sig();
		data->line = readline("minishell> ");
		check_readline_sig(data);
		if (data->line == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (data->line[0])
			add_history(data->line);
		if (lexer(data) < 0)
			continue ;
		// print_tokens(data.token); // For debugging
		data->cmd = parser(data);
		free_token_list(data->token);
		// print_cmds(data.cmd); // For debugging
		if (heredoc_handler(data) < 0)
			continue ;
		if (executer(data) < 0)
			continue ;
		safe_free((void **)&data->line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	if (init_data(&data, envp))
	{
		perror("envp_copy failed");
		return (1);
	}
	prompt_loop(&data);
	// free_all_data(&data);
	return (data.last_status);
}
