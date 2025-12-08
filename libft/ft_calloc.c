/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:45:05 by totake            #+#    #+#             */
/*   Updated: 2025/12/04 22:50:47 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	all_size;
	void	*ret;

	if (nmemb != 0 && size != 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	all_size = nmemb * size;
	ret = safe_alloc(all_size);
	if (!ret)
		return (NULL);
	ft_bzero(ret, all_size);
	return (ret);
}

// #include <stdio.h>

// int	main(int argc, char **argv)
// {
// 	int	*ret1;

// 	// int	*ret2;
// 	(void)argc;
// 	printf("SIZE_MAX: %lu\n", SIZE_MAX);
// 	ret1 = ft_calloc(atoi(argv[1]), sizeof(int));
// 	// ret2 = calloc(atoi(argv[1]), sizeof(char));
// 	// ret1 = ft_calloc(INT_MAX, INT_MAX);
// 	// ret2 = ft_calloc(INT_MAX + 4, 1);
// 	// ret1 = ft_calloc(-5, -5);
// 	// ret2 = calloc(-5, -5);
// 	// printf("ft_calloc: %p\n", ret1);
// 	// printf("calloc: %p\n", ret2);
// 	return (0);
// }
