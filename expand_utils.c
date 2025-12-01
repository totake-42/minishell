/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 02:11:55 by totake            #+#    #+#             */
/*   Updated: 2025/12/01 13:41:54 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *key, t_data *data)
{
	size_t	i;
	size_t	key_len;

	if (!key || key[0] == '\0')
		return (ft_strdup(""));
	key_len = ft_strlen(key);
	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], key, key_len) == 0
			&& data->envp[i][key_len] == '=')
			return (ft_strdup(&data->envp[i][key_len + 1]));
		i++;
	}
	return (ft_strdup(""));
}

char	*extract_var_key(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	if (len == 0)
		return (ft_strdup(""));
	return (ft_substr(str, 0, len));
}

char	*expand_dollar(char *str, size_t *i, t_data *data)
{
	char	*key;
	char	*value;

	key = extract_var_key(&str[*i + 1]);
	value = get_env_value(key, data);
	*i += ft_strlen(key) + 1;
	safe_free((void **)&key);
	return (value);
}

char	*expand_str(char *str, t_data *data)
{
	char *res;
	char *value;
	size_t i;
	size_t res_len;

	res = (char *)xmalloc(1);
	res[0] = '\0';
	res_len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			value = expand_dollar(str, &i, data);
			res = ft_strappend(res, value, &res_len);
			safe_free((void **)&value);
		}
		else
		{
			res = ft_charappend(res, str[i], &res_len);
			i++;
		}
	}
	return (res);
}
