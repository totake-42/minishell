/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:04:29 by totake            #+#    #+#             */
/*   Updated: 2025/12/04 22:51:02 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;

	ret = (char *)safe_alloc(ft_strlen(s) + 1);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, s, ft_strlen(s) + 1);
	return (ret);
}

// #include <stdio.h>
// #include <string.h>

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	printf("ft_strdup: %s\n", ft_strdup(argv[1]));
// 	printf("strdup: %s\n", strdup(argv[1]));
// 	return (0);
// }
