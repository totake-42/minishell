/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:03:09 by totake            #+#    #+#             */
/*   Updated: 2025/12/04 22:51:13 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_set(char const *set, char const c)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*ret;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] != '\0' && ft_is_set(set, s1[start]))
		start++;
	while (end > start && ft_is_set(set, s1[end - 1]))
		end--;
	ret = (char *)safe_alloc((end - start + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, &s1[start], end - start + 1);
	return (ret);
}

// // ft_strtrim("  hogehoge: ", ": "); -> hogehoge
// #include <stdio.h>

// int	main(int argc, char **argv)
// {
// 	(void)argc;

// 	printf("ft_strtrim: %s\n", ft_strtrim(argv[1], argv[2]));
// 	return (0);
// }
