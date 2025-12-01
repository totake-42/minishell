/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 02:00:48 by totake            #+#    #+#             */
/*   Updated: 2025/12/01 13:12:16 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Example usage:
// t_token_type type;
// type = detect_token_type("hello"); // T_WORD
// type = detect_token_type("|");    // T_PIPE
// type = dtect_token_type("<<");  // T_HEREDOC
// type = detect_token_type(">>>"); // T_INVALID

t_token_type	detect_token_type(char *str)
{
	if (str == NULL || str[0] == '\0')
		return (T_INVALID);
	if (!is_delimiter(str[0]))
		return (T_WORD);
	return (detect_delimiter_type(str));
}

t_token_type	detect_delimiter_type(char *str)
{
	if (str[1] == '\0')
	{
		if (str[0] == '|')
			return (T_PIPE);
		if (str[0] == '<')
			return (T_REDIR_IN);
		if (str[0] == '>')
			return (T_REDIR_OUT);
		return (T_INVALID);
	}
	if (str[2] == '\0')
	{
		if (str[0] == '<' && str[1] == '<')
			return (T_HEREDOC);
		if (str[0] == '>' && str[1] == '>')
			return (T_APPEND);
		return (T_INVALID);
	}
	return (T_INVALID);
}
