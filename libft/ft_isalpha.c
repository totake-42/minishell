/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:57:52 by totake            #+#    #+#             */
/*   Updated: 2024/12/12 18:25:34 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_islower(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

static int	ft_isupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if (ft_islower(c) || ft_isupper(c))
		return (1);
	return (0);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	printf("isalpha       : %s\n", (isalpha(argv[1][0]) ? "True" : "False"));
// 	printf("ft_isalpha    : %s\n", (ft_isalpha(argv[1][0]) ? "True" : "False"));
// 	// printf("isalpha    \'\\0\': %d\n", isalpha(0));
// 	// printf("ft_isalpha \'\\0\': %d\n", ft_isalpha(0));
// }
