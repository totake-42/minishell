/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:00:00 by totake            #+#    #+#             */
/*   Updated: 2025/12/01 02:56:42 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Example usage:
// ("abc", 'd', 3) -> "abcd"
// ("abc", "def", 3) -> "abcdef"

char	*ft_charappend(char *str, char c, size_t *len)
{
	char	*new_str;

	new_str = (char *)xmalloc(*len + 2);
	ft_memcpy(new_str, str, *len);
	new_str[*len] = c;
	new_str[*len + 1] = '\0';
	safe_free((void **)&str);
	(*len)++;
	return (new_str);
}

char	*ft_strappend(char *str, char *append_str, size_t *len)
{
	char	*new_str;
	size_t	append_len;

	if (!append_str)
		return (str);
	append_len = ft_strlen(append_str);
	new_str = (char *)xmalloc(*len + append_len + 1);
	if (!new_str)
		return (str);
	ft_memcpy(new_str, str, *len);
	ft_memcpy(new_str + *len, append_str, append_len);
	new_str[*len + append_len] = '\0';
	safe_free((void **)&str);
	*len += append_len;
	return (new_str);
}
