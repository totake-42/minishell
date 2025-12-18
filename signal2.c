/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:49:55 by totake            #+#    #+#             */
/*   Updated: 2025/12/18 14:10:15 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Notify readline that we are starting a new line (reset internal state)
// rl_on_new_line();
// Replace the current input line with an empty string (clear user input)
// rl_replace_line("", 0);
// Redraw the prompt and the (now empty) input line on the screen
// rl_redisplay();
void	check_readline_sig(t_data *data)
{
	if (g_flag == SIGINT)
	{
		data->last_status = 128 + SIGINT;
		g_flag = 0;
	}
}
