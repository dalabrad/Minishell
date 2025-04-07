/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:51:18 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/04/07 14:45:17 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

// LLENAR LISTA POR HEAD/FRONT
int	ft_lstadd_front2(t_pipes **lst, t_pipes *new)
{
	if (!new)
		return (1);
	printf("----> ARGS: NEW NODE %s\n", new->str);
	new->next = *lst;
	*lst = new;
	return (0);
}

// ESTO EN ALGUN MOMENTO SERVIRA
const char	*skip_space(const char *s)
{
	while (*s == ' ' && *s != 0)
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
	printf("-------IS_OPEN---------\n");
	while (s[i])
	{
		printf("\n------>  s[i] <------ de IS_OPEN %c \n", s[i]);
		if (s[i] == '\'' && s[i - 1] != '\\' && !is_double_quote)
			is_single_quote = !is_single_quote;
		else if (s[i] == '\"' && s[i - 1] != '\\' && !is_single_quote)
			is_double_quote = !is_double_quote; // invierte el valor de entrada
		i++;
	}
	return (is_single_quote || is_double_quote);
}
