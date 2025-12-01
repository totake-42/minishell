/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 01:12:33 by totake            #+#    #+#             */
/*   Updated: 2025/12/01 02:13:17 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// For debugging: print all tokens
void	print_tokens(t_token *token)
{
	int	i;

	i = 0;
	while (token != NULL)
	{
		printf("[%d] type=%d str=%s\n", i, token->type, token->str);
		token = token->next;
		i++;
	}
}
