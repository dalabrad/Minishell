/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:35:00 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/08/04 20:02:10 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

// Auxiliar join
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

// Añade caracter al final
char	*ft_strjoin_char_free(char *s1, char c)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	return (ft_strjoin_free(s1, str));
}

// Devuelve el valor de una variable en shell_envp (o NULL)
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

// Procesa y reemplaza todas las ocurrencias de $VAR por su valor en shell_envp
char	*expand_variables(const char *str, t_env *env, int was_quoted, int last_status)
{
	char	*result = ft_strdup("");
	size_t	i = 0;

	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (str[i + 1] == '?')
			{
				i++;
				char *exit_code = ft_itoa(last_status);
				char *tmp = result;
				result = ft_strjoin(tmp, exit_code);
				free(tmp);
				free(exit_code);
				continue;
			}
			if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
			{
				size_t start = ++i;
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
					i++;
				char *var = ft_substr(str, start, i - start);
				char *value = get_env_value_from_list(var, env);
				if (!value)
					value = "";
				char *tmp = result;
				result = ft_strjoin(tmp, value);
				free(tmp);
				free(var);
				continue;
			}
		}
		char buffer[2] = {str[i++], 0};
		char *tmp = result;
		result = ft_strjoin(tmp, buffer);
		free(tmp);
	}
	if (was_quoted == 2) // comillas simples
		return (ft_strdup(str));
	return (result);
}

void	expand_tokens(t_tokens *tokens, t_env *env, int last_status)
{
	t_tokens	*tmp;
	char		*expanded;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->str && tmp->type != ERROR)
		{
			expanded = expand_variables(tmp->str, env, tmp->was_quoted, last_status);
			free(tmp->str);
			tmp->str = expanded;
		}
		tokens = tmp;
		tmp = tmp->next;
	}
}
