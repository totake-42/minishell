/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:26:54 by totake            #+#    #+#             */
/*   Updated: 2025/12/06 19:26:01 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (*head == NULL)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_token;
}

void	skip_whitespace(char **line)
{
	while (**line && is_whitespace(**line))
		(*line)++;
}

t_token	*create_token_node(char *ptr, size_t len, t_data *data)
{
	t_token	*token;
	char	*raw_str;

	if (ptr == NULL || len == 0)
		return (NULL);
	token = (t_token *)ft_calloc(1, sizeof(t_token));
	raw_str = ft_substr(ptr, 0, len);
	token->type = detect_token_type(raw_str);
	token->str = expand_raw_str(raw_str, data);
	token->raw_str = raw_str;
	token->next = NULL;
	return (token);
}

t_token	*build_token_list(t_data *data)
{
	t_token	*head;
	t_token	*new_token;
	size_t	token_len;
	char	*ptr;

	head = NULL;
	ptr = data->line;
	while (*ptr != '\0')
	{
		skip_whitespace(&ptr);
		if (*ptr == '\0')
			break ;
		token_len = next_token_len(ptr);
		if (token_len == 0)
			break ;
		new_token = create_token_node(ptr, token_len, data);
		append_token(&head, new_token);
		ptr += token_len;
	}
	return (head);
}

void	lexer(t_data *data)
{
	if (data->token != NULL)
		free_token_list(data->token);
	data->token = build_token_list(data);
}
