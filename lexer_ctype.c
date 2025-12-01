/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ctype.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 13:52:47 by totake            #+#    #+#             */
/*   Updated: 2025/12/01 13:32:17 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Example usage:
// if (is_whitespace(' ')) == 1
// if (is_delimiter('|')) == 1

// whitespace (' ' or '\t')
int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

// delimiter ('<', '>', '|')
int	is_delimiter(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

// quote (' or ")
int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}
