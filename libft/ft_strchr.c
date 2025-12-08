/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:49:38 by totake            #+#    #+#             */
/*   Updated: 2024/12/13 14:12:35 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s[i] != '\0'
		&& (unsigned char)s[i] != (unsigned char)c)
		i++;
	if ((unsigned char)s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return (NULL);
}

// #include <string.h>

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	// printf("ft_strchr s number is : %s\n", ft_strchr("tripouille", 't'
// 	// + 256));
// 	// printf("strchr s number is : %s\n", strchr("tripouille", 't' + 256));
// 	// printf("ft_strchr s number is : %ld\n", ft_strchr(argv[1], 's')
// 	// - argv[1]);
// 	// printf("strchr s number is : %ld\n", strchr(argv[1], 's') - argv[1]);
// 	// printf("ft_strchr s number is : %s\n", ft_strchr(argv[1], 's'));
// 	printf("strchr s number is : %s\n", ft_strchr(argv[1], 's'));
// 	return (0);
// }
