/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:35:00 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/05/04 18:44:36 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// EXPAND VARIABLES
char *expand_variables(char *str)
{
	if (!str || !*str)
		return str;
	char *temp;
	size_t i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ' && str[i + 1] != '$')
		{
			size_t j = i + 1;
			while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
				j++;

			char *varname = ft_substr(str, i + 1, j - i - 1);
			char *value = getenv(varname);
			if (!value) value = "";

			char *before = ft_substr(str, 0, i);
			char *after = ft_strdup(&str[j]);

			temp = ft_strjoin(before, value);
			free(before);

			char *new_result = ft_strjoin(temp, after);
			free(temp);
			free(after);
			free(varname);
			free(str);
			str = new_result;

			i = i + ft_strlen(value);
		}
		else
			i++;
	}
	return str;
}
