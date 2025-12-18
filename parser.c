/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:16:35 by totake            #+#    #+#             */
/*   Updated: 2025/12/18 14:05:42 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_cmd(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (*head == NULL)
	{
		*head = new_cmd;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_cmd;
}

t_cmd	*create_cmd_node(t_token **token_ptr)
{
	t_cmd		*cmd;
	t_redirect	*r;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	cmd->pid = -1;
	cmd->is_in_child = 0;
	cmd->next = NULL;
	while (*token_ptr != NULL && (*token_ptr)->type != T_PIPE)
	{
		if (is_redirect((*token_ptr)->type))
		{
			r = create_redirect_node(token_ptr);
			append_redirect(&cmd->redirect, r);
		}
		else if ((*token_ptr)->type == T_WORD)
		{
			append_arg(&cmd->argv, (*token_ptr)->str);
			*token_ptr = (*token_ptr)->next;
		}
		else
		{
			*token_ptr = (*token_ptr)->next;
		}
	}
	return (cmd);
}

t_cmd	*build_cmd_list(t_data *data)
{
	t_cmd	*head;
	t_cmd	*new_cmd;
	t_token	*token_ptr;

	head = NULL;
	token_ptr = data->token;
	while (token_ptr != NULL)
	{
		new_cmd = create_cmd_node(&token_ptr);
		append_cmd(&head, new_cmd);
		if (token_ptr && token_ptr->type == T_PIPE)
			token_ptr = token_ptr->next;
	}
	return (head);
}

// print_cmds(data->cmd);
int	parser(t_data *data)
{
	data->cmd = build_cmd_list(data);
	free_token_list(data->token);
	data->token = NULL;
	return (0);
}
