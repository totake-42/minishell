/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:14:00 by totake            #+#    #+#             */
/*   Updated: 2024/10/31 14:49:28 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	size_t buf_size = 32;
// 	char buf1[buf_size];
// 	char buf2[buf_size];

// 	memset(buf1, '\0', buf_size);
// 	fprintf(stdout, "memset    : %s\n", (char *)memset(buf1, 'a', 10));
// 	ft_memset(buf2, '\0', buf_size);
// 	fprintf(stdout, "ft_memset : %s\n", (char *)ft_memset(buf2, 'a', 10));

// 	return (0);
// }