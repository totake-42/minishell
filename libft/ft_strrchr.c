/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:36:31 by totake            #+#    #+#             */
/*   Updated: 2024/12/12 18:23:33 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0 && (unsigned char)s[i] != (unsigned char)c)
		i--;
	if (i >= 0 && (unsigned char)s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return (NULL);
}

// #include <string.h>

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	printf("ft_strrchr s number is : %ld\n", ft_strrchr(argv[1], 's')
// 		- argv[1]);
// 	printf("strrchr s number is : %ld\n", strrchr(argv[1], 's') - argv[1]);
// 	printf("ft_strrchr NULL Character number is : %ld\n", ft_strrchr(argv[1],
// 			'\0') - argv[1]);
// 	printf("strrchr NULL Character number is : %ld\n", strrchr(argv[1], '\0')
// 		- argv[1]);
// 	return (0);
// }
