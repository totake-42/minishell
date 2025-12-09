/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:16:35 by totake            #+#    #+#             */
/*   Updated: 2025/12/09 13:32:47 by totake           ###   ########.fr       */
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
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	cmd->argv = build_argv(token_ptr);
	cmd->redirect = build_redirects(token_ptr);
	cmd->next = NULL;
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

t_cmd	*parser(t_data *data)
{
	// check_tokens(data)
	return (build_cmd_list(data));
}
