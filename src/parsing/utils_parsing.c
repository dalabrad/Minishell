/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:51:18 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/05/10 16:29:10 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

// CLASIFY PATH, IF STRING LOOKS ALIKE
int is_path(const char *str)
{
	if (!str || ft_strlen(str) < 2)
		return 0;

	// absolut
	if (str[0] == '/')
		return 1;

	// relative
	if (ft_strncmp(str, "./", 2) == 0 || ft_strncmp(str, "../", 3) == 0)
		return 1;

	// contains '/'
	if (ft_strchr(str, '/'))
		return 1;

	return 0;
}


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
