/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:35:00 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/08/05 20:22:13 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_utils.h"
#include "minishell_exec.h"
#include "minishell_parsing.h"
#include "minishell_signals.h"

void	append_char_to_result(char **result, char c)
{
	char	buffer[2];

	buffer[0] = c;
	buffer[1] = '\0';
	*result = ft_strjoin_free(*result, buffer);
}

char	*expand_loop(const char *str, t_env *env, int last_status, char *result)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (str[i + 1] == '?')
			{
				i += 2;
				if (handle_exit_status(&result, last_status))
					break ;
				continue ;
			}
			if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
			{
				i = handle_variable(str, ++i, &result, env);
				continue ;
			}
		}
		append_char_to_result(&result, str[i++]);
	}
	return (result);
}

char	*expand_variables(const char *str, t_env *env, int was_quoted,
		int last_status)
{
	char	*result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	result = expand_loop(str, env, last_status, result);
	if (was_quoted == 2)
	{
		free(result);
		return (ft_strdup(str));
	}
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
			expanded = expand_variables(tmp->str, env, tmp->was_quoted,
					last_status);
			free(tmp->str);
			tmp->str = expanded;
		}
		tmp = tmp->next;
	}
}
