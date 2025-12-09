/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:19:12 by totake            #+#    #+#             */
/*   Updated: 2025/12/09 14:57:02 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_quoted_len(char *str, char quote_char, t_data *data)
{
	char	*end;

	end = ft_strchr(str + 1, quote_char);
	if (end == NULL)
		exit_with_error("Unclosed quote", EXIT_FAILURE, data);
	return (end - str + 1);
}

size_t	count_plain_len(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] && !is_quote(str[len]))
		len++;
	return (len);
}

size_t	next_token_len(char *str, t_data *data)
{
	size_t	len;

	if (is_delimiter(str[0]) && (str[0] == str[1]))
		return (2);
	else if (is_delimiter(str[0]))
		return (1);
	len = 0;
	while (str[len] && !is_delimiter(str[len]) && !is_whitespace(str[len]))
	{
		if (is_quote(str[len]))
			len += count_quoted_len(&str[len], str[len], data);
		else
			len++;
	}
	return (len);
}
