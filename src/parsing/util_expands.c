/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_expands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:59:35 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/09/14 22:12:41 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_utils.h"
#include "minishell_exec.h"
#include "minishell_parsing.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
	{
		free(s1);
		return (ft_strdup(""));
	}
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

char	*ft_strjoin_char_free(char *s1, char c)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	return (ft_strjoin_free(s1, str));
}

char	*get_env_value_from_list(const char *name, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	handle_exit_status(char **result, int last_status)
{
	char	*exit_code;

	exit_code = ft_itoa(last_status);
	if (!exit_code)
		return (1);
	*result = ft_strjoin_free(*result, exit_code);
	free(exit_code);
	return (0);
}

/*
 * Maneja expansión de $VAR
 * s[i] apunta al primer carácter tras el '$'
 * Devuelve el índice en s tras el nombre de la variable
 */
size_t	handle_variable(const char *s, size_t i, char **out, t_env *env)
{
	size_t		start;
	char		*name;
	const char	*raw;
	char		*val;

	start = i;
	while (s[i] && (ft_isalnum((unsigned char)s[i]) || s[i] == '_'))
		i++;
	name = ft_substr(s, start, i - start);
	if (!name)
		return (i);
	raw = get_env_value_from_list(name, env);
	free(name);
	if (!raw)
		val = ft_strdup("");
	else
		val = ft_strdup(raw);
	if (!val)
		return (i);
	*out = ft_strjoin_free(*out, val);
	free(val);
	return (i);
}
