/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 02:04:57 by totake            #+#    #+#             */
/*   Updated: 2025/12/01 15:56:44 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_single_quote(char *raw_str)
{
	size_t	len;

	len = count_quoted_len(raw_str, '\'');
	if (len <= 2)
		return (ft_strdup(""));
	return (ft_substr(raw_str, 1, len - 2));
}

char	*handle_double_quote(char *raw_str, t_data *data)
{
	char	*content;
	char	*expanded;
	size_t	len;

	len = count_quoted_len(raw_str, '"');
	if (len <= 2)
		return (ft_strdup(""));
	content = ft_substr(raw_str, 1, len - 2);
	expanded = expand_str(content, data);
	safe_free((void **)&content);
	return (expanded);
}

char	*handle_plain_string(char *raw_str, t_data *data)
{
	char	*expanded;

	expanded = expand_str(raw_str, data);
	return (expanded);
}

char	*expand_next_part(char *raw_str, size_t *i, t_data *data)
{
	char	*part;
	char	*result;
	size_t	len;

	if (raw_str[*i] == '\'' || raw_str[*i] == '"')
		len = (count_quoted_len(&raw_str[*i], raw_str[*i]));
	else
		len = count_plain_len(&raw_str[*i]);
	part = ft_substr(raw_str, *i, len);
	if (raw_str[*i] == '\'')
		result = handle_single_quote(part);
	else if (raw_str[*i] == '"')
		result = handle_double_quote(part, data);
	else
		result = handle_plain_string(part, data);
	safe_free((void **)&part);
	*i += len;
	return (result);
}

char	*expand_raw_str(char *raw_str, t_data *data)
{
	char	*result;
	char	*part_result;
	size_t	i;
	size_t	result_len;

	if (raw_str == NULL)
		return (NULL);
	result = ft_strdup("");
	result_len = 0;
	i = 0;
	while (raw_str[i])
	{
		part_result = expand_next_part(raw_str, &i, data);
		result = ft_strappend(result, part_result, &result_len);
		safe_free((void **)&part_result);
	}
	return (result);
}
