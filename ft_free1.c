/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:02:12 by totake            #+#    #+#             */
/*   Updated: 2025/12/18 14:02:14 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token *token)
{
	t_token	*current;
	t_token	*next;

	current = token;
	while (current != NULL)
	{
		next = current->next;
		if (current->str != NULL)
			safe_free((void **)&current->str);
		safe_free((void **)&current);
		current = next;
	}
}

void	free_redirect_list(t_redirect *redirect)
{
	t_redirect	*current;
	t_redirect	*next;

	current = redirect;
	while (current != NULL)
	{
		next = current->next;
		if (current->filename != NULL)
			safe_free((void **)&current->filename);
		safe_free((void **)&current);
		current = next;
	}
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;
	size_t	i;

	current = cmd;
	while (current != NULL)
	{
		next = current->next;
		if (current->argv != NULL)
		{
			i = 0;
			while (current->argv[i] != NULL)
			{
				safe_free((void **)&current->argv[i]);
				i++;
			}
			safe_free((void **)&current->argv);
		}
		free_redirect_list(current->redirect);
		safe_free((void **)&current);
		current = next;
	}
}

void	free_envp(char **envp)
{
	size_t	i;

	if (envp == NULL)
		return ;
	i = 0;
	while (envp[i] != NULL)
	{
		safe_free((void **)&envp[i]);
		i++;
	}
	safe_free((void **)&envp);
}

void	free_all_data(t_data *data)
{
	safe_free((void **)&data->line);
	free_token_list(data->token);
	data->token = NULL;
	free_cmd_list(data->cmd);
	data->cmd = NULL;
}
