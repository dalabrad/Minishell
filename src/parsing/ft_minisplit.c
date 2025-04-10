/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minisplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:51:29 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/04/09 22:01:07 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "minishell_exec.h" */
#include "../inc/minishell_parsing.h"

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
	size_t	i;
	size_t	j;
	size_t	k;
	/* size_t open_ok; */
	/* char *chop; */

	i = 0;
	j = 0;
	k = 0;
	while (i < w_count)
	{
		while (s[j] != '\0' && s[j] != c)
			j++;
		array[i] = ft_substr(s, k, j - k);
		if (!array[i])
		{
			free_array2(array);
			return NULL;
		}
		i++;
		if (!array[i])
		{
			free_array2(array);
			return NULL;
		}
		i++;
	}
	array[i] = NULL;
	return array;
}

// FT_SPLIT ADAPTED FOR MINI
size_t	count_splitted(const char *s, char c)
{
	size_t	count = 0;
	size_t	i = 0;

	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return count;
}

// FT_SPLIT ADAPTED FOR MINI
char	**ft_minisplit(const char *s, char c, size_t *n)
{
	char	**array;

	if (s == NULL)
		return (NULL);
	s = skip_space(s);
	*n = count_splitted(s, c); // cuenta pipes
	array = (char **)malloc(sizeof(char *) * (*n + 1));
	if (array == NULL)
		return (NULL);
	array = split2array(s, c, array, *n);
	return (array);
}
