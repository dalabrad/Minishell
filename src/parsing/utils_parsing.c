/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:51:18 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/08/06 18:24:24 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	is_path(const char *str)
{
	if (!str || ft_strlen(str) < 2)
		return (0);
	if (str[0] == '/')
		return (1);
	if (ft_strncmp(str, "./", 2) == 0 || ft_strncmp(str, "../", 3) == 0)
		return (1);
	if (ft_strchr(str, '/'))
		return (1);
	return (0);
}

int	ft_lstadd_front2(t_pipes **lst, t_pipes *new)
{
	if (!new)
		return (1);
	new->next = *lst;
	*lst = new;
	return (0);
}

const char	*skip_space(const char *s)
{
	while (*s == ' ' && *s == '\t' && *s != 0)
		s++;
	return (s);
}

size_t	is_open(const char *s)
{
	int		i;
	bool	is_single_quote;
	bool	is_double_quote;

	is_single_quote = false;
	is_double_quote = false;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' && (!i || s[i - 1] != '\\') && !is_double_quote)
			is_single_quote = !is_single_quote;
		else if (s[i] == '"' && (!i || s[i - 1] != '\\') && !is_single_quote)
			is_double_quote = !is_double_quote;
		i++;
	}
	return (is_single_quote || is_double_quote);
}
