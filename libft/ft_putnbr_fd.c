/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:38:20 by totake            #+#    #+#             */
/*   Updated: 2024/12/12 16:38:22 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	un_nbr;

	un_nbr = (unsigned int)n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		un_nbr = (unsigned int)(-1 * n);
	}
	if (un_nbr > 9)
	{
		ft_putnbr_fd(un_nbr / 10, fd);
		ft_putchar_fd('0' + un_nbr % 10, fd);
	}
	else
		ft_putchar_fd('0' + un_nbr, fd);
}
