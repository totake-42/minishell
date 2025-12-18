/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mkstemp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:58:48 by totake            #+#    #+#             */
/*   Updated: 2025/12/18 14:04:14 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_mkstemp(char *template)
{
	int		fd;
	int		counter;
	char	*x_pos;
	char	*temp_str;

	x_pos = &template[ft_strlen(template) - 6];
	counter = 0;
	while (counter < 100000)
	{
		temp_str = ft_itoa(counter);
		if (temp_str == NULL)
			return (-1);
		ft_memset(x_pos, '0', 6);
		ft_memcpy(&x_pos[6 - ft_strlen(temp_str)], temp_str,
			ft_strlen(temp_str));
		safe_free((void **)&temp_str);
		fd = open(template, O_WRONLY | O_CREAT | O_EXCL, 0600);
		if (fd >= 0)
			return (fd);
		if (errno != EEXIST)
			return (-1);
		counter++;
	}
	return (-1);
}
