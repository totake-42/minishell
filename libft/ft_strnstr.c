/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:31:09 by totake            #+#    #+#             */
/*   Updated: 2025/12/03 20:49:56 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_find_little(const char *big, const char *little, size_t i,
		size_t len)
{
	size_t	j;

	j = 0;
	while (little[j] != '\0' && i < len)
	{
		if (big[i] != little[j])
			return (0);
		j++;
		i++;
	}
	if (little[j] == '\0')
		return (1);
	return (0);
}

// If little is an empty string, big is returned;
// if little occurs nowhere in big, NULL is returned;
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		if (is_find_little(big, little, i, len))
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	printf("ft_strnstr: %s\n", ft_strnstr(argv[1], argv[2], atoi(argv[3])));
// 	// printf("strnstr: %s\n", strnstr(argv[1], argv[2], atoi(argv[3])));
// 	return (0);
// }
