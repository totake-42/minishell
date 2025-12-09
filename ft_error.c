/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 01:58:42 by totake            #+#    #+#             */
/*   Updated: 2025/12/09 15:13:27 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_with_error(char *message, int exit_code, t_data *data)
{
	ft_putendl_fd(message, STDERR_FILENO);
	free_all_data(data);
	exit(exit_code);
}
