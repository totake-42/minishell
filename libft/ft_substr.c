/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:19:40 by totake            #+#    #+#             */
/*   Updated: 2025/12/04 22:51:26 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Do not malloc excessive memory
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	s_len;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		len = 0;
	if (len > s_len - start)
		len = s_len - start;
	ret = (char *)safe_alloc(len + 1);
	if (!ret)
		return (NULL);
	if (len > 0)
	{
		while (len--)
		{
			ret[i] = s[start + i];
			i++;
		}
	}
	ret[i] = '\0';
	return (ret);
}

// #include <stdio.h>

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	printf("ft_sbustr: %s\n", ft_substr(argv[1], atoi(argv[2]), atoi(argv[3])));
// 	return (0);
// }
