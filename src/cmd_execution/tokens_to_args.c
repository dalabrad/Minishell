/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:33:07 by dalabrad          #+#    #+#             */
/*   Updated: 2025/05/18 15:50:54 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static size_t	args_size(t_tokens *token_list)
{
	size_t	size;

	size = 0;
	while (token_list)
	{
		if (token_list->type == COMMAND || token_list->type == ARG
			|| token_list->type == OPTION || token_list->type == SETTING)
			size++;
		token_list = token_list->next;
	}
	return (size);
}

char	**tokens_to_args(t_tokens *token_list)
{
	char	**args;
	size_t	size;
	size_t	i;

	size = args_size(token_list);
	if (!size)
		return (NULL);
	args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!args)
	{
		error_msg(MALLOC_ERROR);
		return (NULL);
	}
	i = 0;
	while (token_list && i <= size)
	{
		if (token_list->type == COMMAND || token_list->type == ARG
			|| token_list->type == OPTION || token_list->type == SETTING)
		{
			args[i] = ft_strdup(token_list->str);
			if (!args[i])
			{
				error_msg(MALLOC_ERROR);
				free_array(args);
				return (NULL);
			}
			i++;
		}
		token_list = token_list->next;
	}
	args[i] = NULL;
	return (args);
}
