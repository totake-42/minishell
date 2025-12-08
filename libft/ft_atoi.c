/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:18:30 by totake            #+#    #+#             */
/*   Updated: 2024/12/13 14:18:01 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_isspace(const char *str, int *i)
{
	while (str[*i] != '\0')
	{
		if (str[*i] == ' ' || str[*i] == '\f' || str[*i] == '\n'
			|| str[*i] == '\r' || str[*i] == '\t' || str[*i] == '\v')
			*i = *i + 1;
		else
			return ;
	}
}

// The previous digit is always changed by
// subtracting the value that over LONG_MAX.
int	ft_atoi(const char *nptr)
{
	int			i;
	long long	nbr;
	long long	sign;
	int			digit;

	i = 0;
	nbr = 0;
	ft_isspace(nptr, &i);
	if (nptr[i] == '-')
		sign = -1;
	else
		sign = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		digit = nptr[i] - '0';
		if (sign == 1 && (nbr > (LONG_MAX - digit) / 10))
			return ((int)LONG_MAX);
		if (sign == -1 && (-nbr < (LONG_MIN + digit) / 10))
			return ((int)LONG_MIN);
		nbr = nbr * 10 + digit;
		i++;
	}
	return ((int)(nbr * sign));
}

// #include <stdio.h>

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	// char str[] = "  ---+--+1234ab567";
// 	// char str[] = " \f\n\r\t\v---+--+1234ab567";
// 	// printf("%d\n", ft_atoi(str));
// 	// printf("ft_atoi: %d\n", ft_atoi(argv[1]));
// 	// printf("atoi   : %d\n", atoi(argv[1]));
// 	// printf("ft_atoi LONG_MAX: %d\n", ft_atoi("9223372036854775807"));
// 	// printf("atoi 	LONG_MAX: %d\n", atoi("9223372036854775807"));
// 	// printf("ft_atoi OVER LONG_MAX: %d\n", ft_atoi("9223372036854775808"));
// 	// printf("atoi 	OVER LONG_MAX: %d\n", atoi("9223372036854775808"));
// 	// printf("ft_atoi OVER LONG_MAX: %d\n", ft_atoi("9223372036854775809"));
// 	// printf("atoi 	OVER LONG_MAX: %d\n", atoi("9223372036854775809"));
// 	// printf("ft_atoi LONG_MIN: %d\n", ft_atoi("-9223372036854775808"));
// 	// printf("atoi   	LONG_MIN: %d\n", atoi("-9223372036854775808"));
// 	// printf("ft_atoi OVER LONG_MIN: %d\n", ft_atoi("-9223372036854775809"));
// 	// printf("atoi   	OVER LONG_MIN: %d\n", atoi("-9223372036854775809"));
// 	// printf("LONG_MAX:  %ld\n", LONG_MAX);
// 	// printf("LLONG_MAX: %lld\n", LLONG_MAX);
// 	return (0);
// }