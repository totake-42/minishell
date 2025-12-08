/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:26:37 by totake            #+#    #+#             */
/*   Updated: 2024/12/11 17:29:05 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (NULL);
	while (((unsigned char *)s)[i] != (unsigned char)c && i < n - 1)
		i++;
	if (((unsigned char *)s)[i] == (unsigned char)c)
		return ((void *)(s + i));
	return (NULL);
}

// #include <stdlib.h>
// #include <string.h>

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	// printf("ft_memchr number is %ld\n", (char *)ft_memchr(argv[1],
// 	// argv[2][0],
// 	// 		atoi(argv[3])) - argv[1]);
// 	// printf("memchr number is %ld\n", (char *)memchr(argv[1], argv[2][0],
// 	// 		atoi(argv[3])) - argv[1]);
// 	printf("ft_memchr number is %s\n", (char *)ft_memchr(argv[1], argv[2][0],
// 			atoi(argv[3])));
// 	printf("memchr number is %s\n", (char *)memchr(argv[1], argv[2][0],
// 			atoi(argv[3])));
// 	return (0);
// }
