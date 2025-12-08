/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:54:54 by totake            #+#    #+#             */
/*   Updated: 2024/10/31 14:12:53 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

// #include <stdio.h>
// #include <string.h>

// int	main(int argc, char **argv)
// {
// 	(void)argc;

// 	fprintf(stdout, "strlen       : %lu\n", strlen(argv[1]));
// 	fprintf(stdout, "ft_strlen    : %lu\n", ft_strlen(argv[1]));

// 	return (0);
// }