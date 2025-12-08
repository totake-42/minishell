/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:35:30 by totake            #+#    #+#             */
/*   Updated: 2024/10/31 13:51:50 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
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
// 		fprintf(stdout, "isprint    : i=%d,\t %d,\t %s\n", i, isprint(i),
// 			(isprint(i) ? "True" : "False"));
// 		fprintf(stdout, "ft_isprint : i=%d,\t %d,\t %s\n", i, ft_isprint(i),
// 			(ft_isprint(i) ? "True" : "False"));
// 		i++;
// 	}
// }
