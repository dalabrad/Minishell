/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minisplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:51:29 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/08/05 20:32:34 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

size_t	splitted_len(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

static int	handle_open_check(const char *s, size_t k, size_t j, char **array)
{
	char	*tmp;

	tmp = ft_substr(s, k, j - k);
	if (!tmp)
		return (0);
	if (is_open(tmp))
	{
		free(tmp);
		write(1, "Syntax error\n", 14);
		free_array(array);
		return (0);
	}
	free(tmp);
	return (1);
}

char	**split2array(const char *s, char c, char **array, size_t w_count)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (i < w_count)
	{
		while (s[j] && s[j] != c)
			j++;
		if (!handle_open_check(s, k, j, array))
			return (NULL);
		array[i] = ft_substr(s, k, splitted_len(&s[k], c));
		if (!array[i])
			return (free_array(array), NULL);
		if (s[j])
			j++;
		k = j;
		i++;
	}
	array[i] = NULL;
	return (array);
}

size_t	count_splitted(const char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[0] == c)
		{
			write(1, "Syntax error\n", 14);
			return (0);
		}
		if (s[i] != c)
		{
			count++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
		else if (s[i] == c)
			i++;
	}
	return (count);
}

char	**ft_minisplit(const char *s, char c, size_t *n)
{
	char	**array;

	if (s == NULL)
		return (NULL);
	s = skip_space(s);
	if (!s || *s == '\0')
	{
		*n = 0;
		return (NULL);
	}
	*n = count_splitted(s, c);
	if (*n == 0)
		return (NULL);
	array = malloc(sizeof(char *) * (*n + 1));
	if (!array)
		return (NULL);
	array = split2array(s, c, array, *n);
	return (array);
}
