/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:59:44 by totake            #+#    #+#             */
/*   Updated: 2024/12/11 14:58:50 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	c2;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		c1 = (unsigned char)s1[i];
		c2 = (unsigned char)s2[i];
		if (c1 != c2 || c1 == '\0' || c2 == '\0')
			return (c1 - c2);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	printf("ft_strncmp %d\n", ft_strncmp(argv[1], argv[2], atoi(argv[3])));
// 	printf("strncmp %d\n", strncmp(argv[1], argv[2], atoi(argv[3])));
// 	return (0);
// }
