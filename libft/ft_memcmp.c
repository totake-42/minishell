/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:12:04 by totake            #+#    #+#             */
/*   Updated: 2024/12/13 14:15:57 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i] && i < n - 1)
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int	main(int argc, char **argv)
// {
// 	void	*null_p;

// 	(void)argc;
// 	null_p = NULL;
// 	// printf("ft_memcmp %d\n", ft_memcmp(argv[1], argv[2], atoi(argv[3])));
// 	// printf("memcmp %d\n", memcmp(argv[1], argv[2], atoi(argv[3])));
// 	// printf("memcmp %d\n", memcmp(null_p, null_p, atoi(argv[1])));
// 	return (0);
// }
