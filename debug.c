/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 01:12:33 by totake            #+#    #+#             */
/*   Updated: 2025/12/02 16:11:39 by totake           ###   ########.fr       */
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

// For debugging: print all parsed commands
void	print_cmds(t_cmd *cmd)
{
	int			i;
	int			j;
	t_redirect	*r;

	i = 0;
	while (cmd != NULL)
	{
		printf("[CMD %d]\n", i);
		if (cmd->argv)
		{
			j = 0;
			printf("  argv: ");
			while (cmd->argv[j])
			{
				printf("[%d]=\"%s\" ", j, cmd->argv[j]);
				j++;
			}
			printf("\n");
		}
		else
			printf("  argv: (null)\n");
		if (cmd->redirect)
		{
			printf("  redirects:\n");
			r = cmd->redirect;
			j = 0;
			while (r)
			{
				printf("    [%d] type=%d file=\"%s\"\n", j, r->type,
					r->filename);
				r = r->next;
				j++;
			}
		}
		else
			printf("  redirects: (none)\n");
		cmd = cmd->next;
		i++;
	}
}
