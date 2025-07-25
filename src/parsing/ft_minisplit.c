/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minisplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:51:29 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/07/08 19:50:01 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"
#include "minishell_exec.h"

// LENGTH OF SPLITTED FOR SUBSTR
size_t	splitted_len(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

// SPLIT TO ARRAY (THEN TO RES)
char	**split2array(const char *s, char c, char **array, size_t w_count)
{
	size_t	i = 0, j = 0, k = 0;
	char	*chop;
	size_t	open_ok;

	while (i < w_count)
	{
		while (s[j] != '\0' && s[j] != c)
			j++;
		chop = ft_substr(s, k, (j - k));
		open_ok = is_open(chop);
		if (open_ok != 0)
		{
			free(chop);
			write(1, "Syntax error\n", 14);
			return (NULL);
		}
		free(chop);
		array[i] = ft_substr(s, k, splitted_len(&s[k], c));
		if (array[i] == NULL)
			return (free_array(array), NULL);
		if (s[j] != '\0')
			j++;
		k = j;
		i++;
	}
	array[i] = NULL;
	return (array);
}

// COUNT SPLITTED PIPES/TOKENS/ARGS
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

// FT_SPLIT ADAPTED FOR MINI
char	**ft_minisplit(const char *s, char c, size_t *n)
{
	char	**array;

	if (s == NULL)
		return (NULL);

	s = skip_space(s); // salta espacios iniciales
	if (!s || *s == '\0') // si todo son espacios, se considera como un string vacío
	{
		*n = 0;
		return (NULL);
	}

	*n = count_splitted(s, c);
	if (*n == 0)
		return (NULL); // no hay nada que dividir

	array = malloc(sizeof(char *) * (*n + 1));
	if (!array)
		return (NULL);

	array = split2array(s, c, array, *n);
	return (array);
}
