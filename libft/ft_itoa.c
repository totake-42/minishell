/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:48:00 by totake            #+#    #+#             */
/*   Updated: 2025/12/04 22:50:51 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	buf[12];
	char	*p;
	char	*ret;
	int		flag;

	ft_bzero(buf, 12);
	p = buf + 11;
	flag = (n < 0);
	if (n == 0)
		*--p = '0';
	while (n)
	{
		if (n > 0)
			*--p = '0' + (n % 10);
		else if (n < 0)
			*--p = '0' + (-1 * (n % 10));
		n /= 10;
	}
	if (flag)
		*--p = '-';
	ret = (char *)safe_alloc(sizeof(char) * (ft_strlen(p) + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, p, ft_strlen(p) + 1);
	return (ret);
}
