/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:51:18 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/04/15 19:37:21 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

// PRINT TOKENS
void	print_tokens(t_tokens *list)
{
	if (!list)
	{
		printf("→ No tokens to show.\n");
		return;
	}

	while (list)
	{
		printf("→ Token: %-15s | Type: %-12s | Quoted: %s\n",
			list->str,
			token_type_str(list->type),
			list->was_quoted ? "yes" : "no");
		list = list->next;
	}
}

// LLENAR LISTA POR HEAD/FRONT
int	ft_lstadd_front2(t_pipes **lst, t_pipes *new)
{
	if (!new)
		return (1);
	new->next = *lst;
	*lst = new;
	return (0);
}

// IGNORE SPACES  TABS
const char	*skip_space(const char *s)
{
	while (*s == ' ' && *s == '\t' && *s != 0)
		s++;
	return (s);
}

// CHECK-IF OPEN QUOTES
size_t	is_open(const char *s)
{
	int		i;
	bool	is_single_quote;
	bool	is_double_quote;

	is_single_quote = false; // 0
	is_double_quote = false; // 0
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' && s[i - 1] != '\\' && !is_double_quote)
			is_single_quote = !is_single_quote;
		else if (s[i] == '\"' && s[i - 1] != '\\' && !is_single_quote)
			is_double_quote = !is_double_quote; // invierte el valor de entrada
		i++;
	}
	return (is_single_quote || is_double_quote);
}
