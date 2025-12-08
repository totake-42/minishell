/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:15:31 by totake            #+#    #+#             */
/*   Updated: 2024/12/13 14:01:50 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_ptr;
	const unsigned char	*src_ptr;
	size_t				i;

	dest_ptr = (unsigned char *)dest;
	src_ptr = (const unsigned char *)src;
	if (dest_ptr < src_ptr)
	{
		i = 0;
		while (i < n)
		{
			dest_ptr[i] = src_ptr[i];
			i++;
		}
	}
	else if (dest_ptr > src_ptr)
	{
		while (n--)
		{
			dest_ptr[n] = src_ptr[n];
		}
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// void	*null_p;
// char	buf1[] = "123456789";

// char	buf2[] = "123456789";
// printf("Before memmove  : %s\n", buf1);
// memmove(&buf1[4], &buf1[2], 5);
// printf("After memmove   : %s\n", buf1);
// printf("Before ft_memmove : %s\n", buf2);
// ft_memmove(&buf2[4], &buf2[2], 5);
// printf("After ft_memmove  : %s\n", buf2);
// char	buf2;
// null_p = NULL;
// memmove(&buf1, null_p, 5);
// ft_memmove(null_p, buf1, 5);
// 	return (0);
// }
