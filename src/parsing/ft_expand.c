/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:35:00 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/06/21 16:47:37 by vlorenzo         ###   ########.fr       */
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

// Devuelve valor de una variable en t_env, o "" si no está definida
char	*get_env_value(char *name, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*expand_variables(char *str, t_env *env)
{
	char	*expanded;
	char	var_name[256];
	char	*var_value;
	int		i;

	expanded = ft_strdup("");
	while (*str)
	{
		if (*str == '$' && ft_isalpha(*(str + 1)))
		{
			str++;
			i = 0;
			while (ft_isalnum(*str) || *str == '_')
				var_name[i++] = *str++;
			var_name[i] = '\0';
			var_value = get_env_value(var_name, env);
			printf("-> Expandiendo $%s = '%s'\n", var_name, var_value);
			expanded = ft_strjoin_free(expanded, var_value);
		}
		else
			expanded = ft_strjoin_char_free(expanded, *str++);
	}
	return (expanded);
}

void	expand_tokens(t_tokens *tokens, t_env *env)
{
	t_tokens	*tmp;
	char		*expanded;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->str && tmp->type != ERROR)
		{
			expanded = expand_variables(tmp->str, env);
			free(tmp->str);
			tmp->str = expanded;
		}
		tmp = tmp->next;
	}
}
