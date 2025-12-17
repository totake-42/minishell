/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:41:07 by totake            #+#    #+#             */
/*   Updated: 2025/12/17 15:28:54 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect(t_token_type type)
{
	return (type == T_REDIRECT_IN || type == T_REDIRECT_OUT || type == T_APPEND
		|| type == T_HEREDOC);
}

void	append_redirect(t_redirect **head, t_redirect *new_redirect)
{
	t_redirect	*current;

	if (*head == NULL)
	{
		*head = new_redirect;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_redirect;
}

t_redirect_type	token_type_to_redirect_type(t_token_type type)
{
	if (type == T_REDIRECT_IN)
		return (R_INPUT);
	if (type == T_REDIRECT_OUT)
		return (R_OUTPUT);
	if (type == T_APPEND)
		return (R_APPEND);
	if (type == T_HEREDOC)
		return (R_HEREDOC);
	return (R_INPUT);
}

t_redirect	*create_redirect_node(t_token **token_ptr)
{
	t_redirect *redirect;

	if (!token_ptr || !*token_ptr || !is_redirect((*token_ptr)->type))
		return (NULL);
	redirect = (t_redirect *)ft_calloc(1, sizeof(t_redirect));
	redirect->type = token_type_to_redirect_type((*token_ptr)->type);
	*token_ptr = (*token_ptr)->next;
	if (*token_ptr && (*token_ptr)->type == T_WORD)
	{
		redirect->filename = ft_strdup((*token_ptr)->str);
		if ((*token_ptr)->raw_str != NULL && (*token_ptr)->raw_str[0] == '\'')
			redirect->should_expand = 0;
		else
			redirect->should_expand = 1;
		*token_ptr = (*token_ptr)->next;
	}
	redirect->next = NULL;
	return (redirect);
}