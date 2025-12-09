/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 23:38:17 by totake            #+#    #+#             */
/*   Updated: 2025/12/10 08:15:08 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_heredocs(t_cmd *cmd)
{
	t_redirect	*r;

	while (cmd != NULL)
	{
		r = cmd->redirect;
		while (r != NULL)
		{
			if (r->type == R_INPUT && r->filename != NULL
				&& ft_strnstr(r->filename, "/tmp/minishell_heredoc",
					ft_strlen(r->filename)))
			{
				unlink(r->filename);
			}
			r = r->next;
		}
		cmd = cmd->next;
	}
}

int	handle_heredocs(t_cmd *cmd, t_data *data)
{
	t_redirect	*redirect;

	set_ignore_sig();
	while (cmd != NULL)
	{
		redirect = cmd->redirect;
		while (redirect != NULL)
		{
			if (redirect->type == R_HEREDOC)
			{
				if (handle_heredoc(redirect, data) == -1)
					return (-1);
			}
			redirect = redirect->next;
		}
		cmd = cmd->next;
	}
	set_readline_sig();
	return (0);
}

int	heredoc_handler(t_data *data)
{
	if (handle_heredocs(data->cmd, data) < 0)
	{
		data->last_status = 130;
		free_cmd_list(data->cmd);
		data->cmd = NULL;
		return (-1);
	}
	return (0);
}
