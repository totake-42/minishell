/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:24:20 by totake            #+#    #+#             */
/*   Updated: 2025/12/09 17:31:07 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return (1) case: unclosed quote found
// return (0) case: all quotes are closed
int	has_unclosed_quote(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == '\0')
				return (1);
			i++;
		}
		else
			i++;
	}
	return (0);
}

// return (0) case: all tokens are valid
// return (-1) case: syntax error found
int	check_invalid_token(t_token *token)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		if (current->type == T_INVALID)
		{
			ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
			return (-1);
		}
		current = current->next;
	}
	return (0);
}

int	check_pipe_error(t_token *token)
{
	t_token	*current;

	if (token->type == T_PIPE)
	{
		ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
		return (-1);
	}
	current = token;
	while (current != NULL)
	{
		if (current->type == T_PIPE)
		{
			if (current->next == NULL || current->next->type == T_PIPE)
			{
				ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
				return (-1);
			}
		}
		current = current->next;
	}
	return (0);
}

int	check_redirect_error(t_token *token)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		if (current->type == T_REDIRECT_IN || current->type == T_REDIRECT_OUT
			|| current->type == T_APPEND || current->type == T_HEREDOC)
		{
			if (current->next == NULL || current->next->type == T_PIPE
				|| current->next->type == T_REDIRECT_IN
				|| current->next->type == T_REDIRECT_OUT
				|| current->next->type == T_APPEND
				|| current->next->type == T_HEREDOC)
			{
				ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
				return (-1);
			}
		}
		current = current->next;
	}
	return (0);
}

int	check_token(t_token *token)
{
	if (token == NULL)
		return (0);
	if (check_invalid_token(token) == -1)
		return (-1);
	if (check_pipe_error(token) == -1)
		return (-1);
	if (check_redirect_error(token) == -1)
		return (-1);
	return (0);
}
