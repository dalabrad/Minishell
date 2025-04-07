/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clasifyTokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:51:38 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/04/07 13:14:59 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

// CLASIFY TOKENS
t_TokenType	clasify_token(const char *str)
{
	enum t_TokenType	type;
	int					i;

	i = 0;
	type = 0;
	// REDIRECTIONS
	if (ft_strcmp(&str[i], "<"))
	{
		if (i == 0)
		{
			if (ft_strcmp(&str[i + 1], "<") && str[i + 2] != '<')
				return (printf("HEREDOC %s\n", str));
			else if (ft_strcmp(&str[i + 1], "<") && str[i + 2] == ' ')
				return (RED_IN);
		}
		else if (i != 0 && str[i - 1] != ' ')
			return (ERROR);
		else if (i != 0 && str[i + 1] == '<' && str[i + 2] != '<')
			return (HEREDOC);
		else if (i != 0 && ft_strcmp(&str[i + 1], "<") && str[i + 2] == ' ')
			return (RED_IN);
	}
	if (ft_strcmp(&str[i], ">"))
	{
		if (i == 0)
		{
			if (ft_strcmp(&str[i + 1], ">") && str[i + 2] != '>')
				return (APPEND_OUT);
			else if (ft_strcmp(&str[i + 1], ">") && str[i + 2] == ' ')
				return (RED_OUT);
		}
		else if (i != 0 && str[i - 1] != ' ')
			return (ERROR);
		else if (i != 0 && str[i + 1] == '>' && str[i + 2] != '>')
			return (APPEND_OUT);
		else if (i != 0 && ft_strcmp(&str[i + 1], ">") && str[i + 2] == ' ')
			return (RED_OUT);
	}
	// OPTIONS/FLAG
	if (ft_strcmp(&str[i], "-") && (str[i + 1]))
		return (OPTION);
	return (type);
}

// CHECK-IF TOKEN IN-QUOTES
char	*poly_substr(const char *s, size_t *i)
{
	int		init_token;
	bool	is_single;
	bool	is_double;

	init_token = *i;
	is_single = false;
	is_double = false;
	while (s[*i] != 0)
	{
		if (s[*i] == '"' && !is_single)
			is_double = !is_double;
		if (s[*i] == '\'' && !is_double)
			is_single = !is_single;
		if (s[*i] == ' ' && is_single == false && is_double == false) 
			return (ft_substr(s, init_token, *i)); // NOTE: true!=1; false=0
		(*i)++;
	}
	return (ft_substr(s, init_token, *i));
}

// CHECK ARGS FROM PIPES
t_tokens	*check_args(char *pipes, size_t *i_words)
{
	t_tokens	*token;
	size_t		k;

	k = 0;
	i_words = 0;
	token = malloc(sizeof(t_tokens));
	*token = (t_tokens){0, 0, NULL, NULL}; // Init struct t_tokens
	printf("\n-----> ENTRO?????????????????\n");
	while (pipes[k++])
	{
		token->str = poly_substr(pipes, &k);
		clasify_token(token->str);
		token = token->next;
		i_words++;
	}
	return (token);
}
