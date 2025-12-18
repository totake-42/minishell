/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:39:16 by totake            #+#    #+#             */
/*   Updated: 2025/12/18 14:06:51 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Example usage:
// char **argv = NULL;
// argv = NULL;
// append_arg(&argv, "echo");
// argv = ["echo", NULL];
// append_arg(&argv, "hello");
// argv = ["echo", "hello", NULL];
// append_arg(&argv, "world");
// argv = ["echo", "hello", "world", NULL]
void	append_arg(char ***argv, char *arg)
{
	char	**new_argv;
	size_t	count;
	size_t	i;

	count = 0;
	if (*argv)
	{
		while ((*argv)[count])
			count++;
	}
	new_argv = (char **)ft_calloc(count + 2, sizeof(char *));
	i = 0;
	while (i < count)
	{
		new_argv[i] = (*argv)[i];
		i++;
	}
	new_argv[count] = ft_strdup(arg);
	if (i > 0)
		safe_free((void **)argv);
	*argv = new_argv;
}
