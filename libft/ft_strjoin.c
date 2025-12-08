/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:49:53 by totake            #+#    #+#             */
/*   Updated: 2025/12/04 22:51:05 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	ret_size;

	if (!s1 || !s2)
		return (NULL);
	ret_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	ret = (char *)safe_alloc(ret_size);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, ret_size);
	ft_strlcat(ret, s2, ret_size);
	return (ret);
}

// #include <stdio.h>

// int	main(int argc, char **argv)
// {
// 	(void)argc;

// 	printf("ft_strjoin: %s\n", ft_strjoin(argv[1], argv[2]));
// 	return (0);
// }
