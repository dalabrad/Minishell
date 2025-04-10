/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clasifyTokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:51:38 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/04/10 13:40:22 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "minishell_exec.h" */
#include "../inc/minishell_parsing.h"

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
				{
					printf("HEREDOC %s\n", str);
					return (HEREDOC);
				}
			else if (ft_strcmp(&str[i + 1], "<") && str[i + 2] == ' ')
				{
					printf("RED_IN %s\n", str);
					return (RED_IN);
				}
		}
		else if (i != 0 && str[i - 1] != ' ')
			{
				printf("ERROR %s\n", str);
				return (ERROR);
			}
		else if (i != 0 && str[i + 1] == '<' && str[i + 2] != '<')
			{
				printf("HEREDOC %s\n", str);
				return (HEREDOC);
			}
		else if (i != 0 && ft_strcmp(&str[i + 1], "<") && str[i + 2] == ' ')
			{
				printf("RED_IN %s\n", str);
				return (RED_IN);
			}
	}
	if (ft_strcmp(&str[i], ">"))
	{
		if (i == 0)
		{
			if (ft_strcmp(&str[i + 1], ">") && str[i + 2] != '>')
			{
				printf("APPEND_OUT %s\n", str);
				return (APPEND_OUT);
			}
			else if (ft_strcmp(&str[i + 1], ">") && str[i + 2] == ' ')
			{
				printf("RED_OUT %s\n", str);
				return (RED_OUT);
			}
		}
		else if (i != 0 && str[i - 1] != ' ')
		{
			printf("ERROR %s\n", str);
			return (ERROR);
		}
		else if (i != 0 && str[i + 1] == '>' && str[i + 2] != '>')
		{
			printf("APPEND_OUT %s\n", str);
			return (APPEND_OUT);
		}
		else if (i != 0 && ft_strcmp(&str[i + 1], ">") && str[i + 2] == ' ')
		{
			printf("RED_OUT %s\n", str);
			return (RED_OUT);
		}
	}
	printf("OTRA COSA -----------CLASIFY TOKEN ");
	// OPTIONS/FLAG
	if (ft_strcmp(&str[i], "-") && (str[i + 1]))
		{
			printf("OPTION %s\n", str);
			return (OPTION);
		}
	
	return (type);
}

// ENUM TO STRING
const char *token_type_str(t_TokenType type)
{
	switch (type)
	{
		case RED_IN: return "RED_IN";
		case RED_OUT: return "RED_OUT";
		case HEREDOC: return "HEREDOC";
		case APPEND_OUT: return "APPEND_OUT";
		case OPTION: return "OPTION";
		case COMMAND: return "COMMAND";
		case SETTING: return "SETTING";
		case ARG: return "ARG";
		case ERROR: return "ERROR";
		default: return "UNKNOWN";
	}
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
t_tokens	*check_args_fixed(const char *pipes, size_t *i_words)
{
	t_tokens	*head = NULL;
	t_tokens	*curr = NULL;
	size_t		k = 0;
/* 	t_TokenType *token;

	token = malloc(sizeof(t_TokenType)); */
	printf("----->ENTRO??? -----------\n");
	while (pipes[k])
	{
		while (pipes[k] == ' ')
			k++;
		if (!pipes[k])
			break;

		t_tokens *new_tok = malloc(sizeof(t_tokens));
		if (!new_tok)
			break;
			
		new_tok->str = poly_substr(pipes, &k);
		(*i_words)++;
		new_tok->next = NULL;
		new_tok->skip = 0;
		new_tok->was_quoted = 0;
		new_tok->type = clasify_token(new_tok->str); // Asignamos tipo del token

		printf("→ Token: %-15s | Type: %-12s\n",
			new_tok->str, token_type_str(new_tok->type));

		if (!head)
			head = new_tok;
		else
			curr->next = new_tok;
		curr = new_tok;
		}
	return head;
}
