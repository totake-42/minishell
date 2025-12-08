/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:23:57 by totake            #+#    #+#             */
/*   Updated: 2024/10/26 20:33:48 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	printf("isalnum       : %d, %s\n", isalnum(argv[1][0]),
// 		(isalnum(argv[1][0]) ? "True" : "False"));
// 	printf("ft_isalnum    : %d, %s\n", ft_isalnum(argv[1][0]),
// 		(ft_isalnum(argv[1][0]) ? "True" : "False"));
// 	printf("isalnum    \'\\0\': %d\n", isalnum(0));
// 	printf("ft_isalnum \'\\0\': %d\n", ft_isalnum(0));
// }
