/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:50:29 by totake            #+#    #+#             */
/*   Updated: 2024/10/31 13:16:29 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int	i;

// 	i = -1;
// 	while (i <= 300)
// 	{
// 		fprintf(stdout, "isascii       : i=%d, %d, %s\n", i, isascii(i),
// 			(isascii(i) ? "True" : "False"));
// 		fprintf(stdout, "ft_isascii    : i=%d, %d, %s\n", i, ft_isascii(i),
// 			(ft_isascii(i) ? "True" : "False"));
// 		i++;
// 	}
// }
