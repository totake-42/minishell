/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:50:33 by totake            #+#    #+#             */
/*   Updated: 2024/10/31 15:33:20 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	size_t buf_size = 32;
// 	char buf1[buf_size];
// 	char buf2[buf_size];
// 	size_t i;

// 	bzero(buf1, buf_size);
// 	ft_bzero(buf2, buf_size);
// 	i = 0;
// 	while (i < buf_size)
// 	{
// 		fprintf(stdout, "%d,", buf1[i]);
// 		i++;
// 	}
// 	i = 0;
// 	fprintf(stdout, "\n");
// 	while (i < buf_size)
// 	{
// 		fprintf(stdout, "%d,", buf2[i]);
// 		i++;
// 	}
// 	fprintf(stdout, "\n");

// 	return (0);
// }