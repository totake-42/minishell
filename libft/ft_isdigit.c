/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:05:19 by totake            #+#    #+#             */
/*   Updated: 2024/10/26 20:18:31 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	printf("isdigit       : %d, %s\n", isdigit(argv[1][0]),
// 		(isdigit(argv[1][0]) ? "True" : "False"));
// 	printf("ft_isdigit    : %d, %s\n", ft_isdigit(argv[1][0]),
// 		(ft_isdigit(argv[1][0]) ? "True" : "False"));
// 	// printf("isdigit    \'\\0\': %d\n", isdigit(0));
// 	// printf("ft_isdigit \'\\0\': %d\n", ft_isdigit(0));
// }
