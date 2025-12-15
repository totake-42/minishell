/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:49:55 by totake            #+#    #+#             */
/*   Updated: 2025/12/15 12:04:35 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_flag = 0;

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		g_flag = SIGINT;
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

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

void	set_readline_sig(void)
{
	struct sigaction	act1;
	struct sigaction	act2;

	ft_bzero(&act1, sizeof(struct sigaction));
	ft_bzero(&act2, sizeof(struct sigaction));
	act1.sa_handler = handler;
	act1.sa_flags = SA_RESTART;
	sigemptyset(&act1.sa_mask);
	if (sigaction(SIGINT, &act1, NULL) < 0)
		perror("fatal: sigaction");
	act2.sa_handler = SIG_IGN;
	act2.sa_flags = 0;
	sigemptyset(&act2.sa_mask);
	if (sigaction(SIGQUIT, &act2, NULL) < 0)
		perror("fatal: sigaction");
}

void	set_ignore_sig(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(struct sigaction));
	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (sigaction(SIGINT, &act, NULL) < 0)
		perror("fatal: sigaction");
	if (sigaction(SIGQUIT, &act, NULL) < 0)
		perror("fatal: sigaction");
}

void	set_child_sig(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(struct sigaction));
	act.sa_handler = SIG_DFL;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (sigaction(SIGINT, &act, NULL) < 0)
		perror("fatal: sigaction");
	if (sigaction(SIGQUIT, &act, NULL) < 0)
		perror("fatal: sigaction");
}

void	set_heredoc_sig(void)
{
	struct sigaction	act1;
	struct sigaction	act2;

	ft_bzero(&act1, sizeof(struct sigaction));
	ft_bzero(&act2, sizeof(struct sigaction));
	act1.sa_handler = SIG_DFL;
	act1.sa_flags = 0;
	sigemptyset(&act1.sa_mask);
	if (sigaction(SIGINT, &act1, NULL) < 0)
		perror("fatal: sigaction");
	act2.sa_handler = SIG_IGN;
	act2.sa_flags = 0;
	sigemptyset(&act2.sa_mask);
	if (sigaction(SIGQUIT, &act2, NULL) < 0)
		perror("fatal: sigaction");
}
