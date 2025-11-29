/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:37:38 by totake            #+#    #+#             */
/*   Updated: 2025/11/29 15:39:08 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *dest_ptr;
	const unsigned char *src_ptr;
	size_t i;

	dest_ptr = dest;
	src_ptr = src;
	i = 0;
	while (i < n)
	{
		dest_ptr[i] = src_ptr[i];
		i++;
	}
	return (dest);
}

char *ft_strdup(const char *s)
{
	char *ret;

	ret = (char *)malloc(ft_strlen(s) + 1);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, s, ft_strlen(s) + 1);
	return (ret);
}
