/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clasifyTokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:51:38 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/04/15 19:37:27 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

// CLASIFY TOKENS
t_TokenType clasify_token(const char *str)
{
	if (!str)
		return ERROR;
	if (!ft_strcmp(str, "<"))
		return RED_IN;
	if (!ft_strcmp(str, ">"))
		return RED_OUT;
	if (!ft_strcmp(str, "<<"))
		return HEREDOC;
	if (!ft_strcmp(str, ">>"))
		return APPEND_OUT;
	if (str[0] == '-' && str[1])
		return OPTION;
	if (strchr(str, '='))
		return SETTING;
	if (!ft_strcmp(str, "|"))
		return ERROR; // Podés definir PIPE si lo agregás al enum
	return ARG;
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

// SET COMMAND TYPE
void set_command_type(t_tokens *tokens)
{
	t_tokens *tmp = tokens;

	while (tmp)
	{
		// Saltamos redirecciones y sus argumentos
		if (tmp->type == RED_IN || tmp->type == RED_OUT ||
			tmp->type == HEREDOC || tmp->type == APPEND_OUT)
		{
			tmp = tmp->next;
			if (tmp) tmp = tmp->next;
			continue;
		}

		// Si es ARG u OPTION, y NO está quoted → es un comando
		if ((tmp->type == ARG || tmp->type == OPTION) && tmp->was_quoted == 0)
		{
			tmp->type = COMMAND;
			break;
		}
		tmp = tmp->next;
	}
}


// SPLIT WORDS: HANDLES QUOTES AND REDIR
char *poly_substr(const char *s, size_t *i, int *was_quoted)
{
	size_t	start = *i;
	bool	in_single = false;
	bool	in_double = false;
	*was_quoted = 0;

	if (s[*i] == '|' || s[*i] == '<' || s[*i] == '>')
	{
		if ((s[*i] == '<' || s[*i] == '>') && s[*i + 1] == s[*i])
			(*i) += 2;
		else
			(*i)++;
		return ft_substr(s, start, *i - start);
	}

	while (s[*i])
	{
		if (s[*i] == '"' && !in_single)
		{
			in_double = !in_double;
			*was_quoted = 1;
		}
		else if (s[*i] == '\'' && !in_double)
		{
			in_single = !in_single;
			*was_quoted = 1;
		}
		else if ((s[*i] == ' ' || s[*i] == '|' || s[*i] == '<' || s[*i] == '>') &&
				 !in_single && !in_double)
		{
			break;
		}
		(*i)++;
	}
	return ft_substr(s, start, *i - start);
}

// SEPARAR Y CLASIFICAR TOKENS
t_tokens *check_args_fixed(const char *input, size_t *i_words)
{
	t_tokens	*head = NULL;
	t_tokens	*curr = NULL;
	size_t		k = 0;

	printf("-----> Tokenizing: [%s]\n", input);
	while (input[k])
	{
		while (input[k] == ' ')
			k++;
		if (!input[k])
			break;

		t_tokens *new_tok = malloc(sizeof(t_tokens));
		if (!new_tok)
			break;

		new_tok->str = poly_substr(input, &k, &new_tok->was_quoted);
		new_tok->type = clasify_token(new_tok->str);
		new_tok->was_quoted = (new_tok->str[0] == '"' || new_tok->str[0] == '\'');
		new_tok->skip = 0;
		new_tok->next = NULL;

		(*i_words)++;

		if (!head)
			head = new_tok;
		else
			curr->next = new_tok;
		curr = new_tok;
	}
	set_command_type(head);
	return head;
}
