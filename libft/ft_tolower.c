/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:23:41 by totake            #+#    #+#             */
/*   Updated: 2024/12/09 14:48:29 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	return (c);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	printf("ft_tolower: %c\n", ft_tolower((int)argv[1][0]));
// 	printf("tolower: %c\n", tolower((int)argv[1][0]));
// 	return (0);
// }
