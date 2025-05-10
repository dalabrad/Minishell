/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:51:46 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/05/10 11:45:01 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

// HANDLE TOKEN ALLOC FAILURE
int handle_token_alloc_fail(char **segments, char *line)
{
	free_array(segments);
	free(line);
	return (0);
}

// INIT STRUCT T_PIPES
t_pipes	*init_struct(t_pipes *args)
{
	args = malloc(sizeof(t_pipes));
	if (!args)
		return (NULL);
	args->index = 0;
	args->str = NULL;
	args->next = NULL; 
	return (args);
}

// INIT PIPE SEGMENTS FOR TOKENIZING
int init_pipe_segments(char *line, char ***segments, size_t *n)
{
	*segments = ft_minisplit(line, '|', n);
	if (!*segments)
	{
		free(line);
		return (0);
	}
	return (1);
}

// ARRAY OF TOKENS BY SEGMENT READY FOR SENDING TO EXEC
t_tokens **init_tokens_by_segment(size_t count)
{
	t_tokens **arr = malloc(sizeof(t_tokens *) * (count + 1));
	if (!arr)
	{
		perror("malloc tokens_by_segment");
		return (NULL);
	}
	size_t i = 0;
	while (i <= count)
		arr[i++] = NULL;
	return (arr);
}

