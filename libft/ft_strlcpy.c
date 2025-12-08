/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:20:33 by totake            #+#    #+#             */
/*   Updated: 2024/12/11 15:03:29 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char buf2[] = "123456789";
// 	size_t len;

// 	printf("Before ft_strlcpy : %s\n", buf2);
// 	len = ft_strlcpy(buf2, "abc", 4);
// 	printf("After ft_strlcpy  : %s\n", buf2);
// 	printf("Return Value: %zu\n", len);
// 	return (0);
// }