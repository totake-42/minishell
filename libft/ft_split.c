/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:57:54 by totake            #+#    #+#             */
/*   Updated: 2025/12/18 18:04:41 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	strings_count(char const *s, char c)
{
	size_t	s_count;
	size_t	new_word;
	size_t	i;

	s_count = 0;
	new_word = 1;
	i = 0;
	if (s[0] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			new_word = 1;
		else if (new_word == 1)
		{
			new_word = 0;
			s_count++;
		}
		i++;
	}
	return (s_count);
}

static size_t	word_count(char const *s, char c, int i)
{
	size_t	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static void	free_all(char ***ret_ptr, size_t j)
{
	char	**ret;

	ret = *ret_ptr;
	while (j > 0)
	{
		free(ret[--j]);
		ret[j] = NULL;
	}
	free(ret);
	*ret_ptr = NULL;
}

static void	fill(char const *s, char c, char **ret, size_t s_count)
{
	size_t	i;
	size_t	j;
	size_t	w_count;

	i = 0;
	j = 0;
	while (s[i] && j < s_count)
	{
		while (s[i] == c)
			i++;
		w_count = word_count(s, c, i);
		ret[j] = (char *)safe_alloc(w_count + 1);
		if (!ret[j])
		{
			free_all(&ret, j);
			return ;
		}
		ft_strlcpy(ret[j], &s[i], w_count + 1);
		i += w_count;
		j++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	s_count;

	if (s == NULL)
		return (NULL);
	s_count = strings_count(s, c);
	ret = (char **)safe_alloc(sizeof(char *) * (s_count + 1));
	if (!ret)
		return (NULL);
	ret[s_count] = NULL;
	fill(s, c, ret, s_count);
	return (ret);
}
