/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:34:02 by totake            #+#    #+#             */
/*   Updated: 2024/12/13 15:08:29 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_ptr;
	const unsigned char	*src_ptr;
	size_t				i;

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

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	size_t buf_size = 32;
// 	char buf1[buf_size];
// char buf2[buf_size];
// char buf3[buf_size];
// void *null_p;

// null_p = NULL;
// bzero(buf1, buf_size);
// bzero(buf2, buf_size);
// memset(buf3, 'a', 5);
// fprintf(stdout, "memcpy    : %s\n", (char *)memcpy(buf1, buf3, 5));
// fprintf(stdout, "ft_memcpy : %s\n", (char *)ft_memcpy(buf2, buf3, 5));
// printf("%p\n", ft_memcpy(null_p, buf1, 0));
// ft_memcpy(null_p, buf1, 5);

// 	return (0);
// }