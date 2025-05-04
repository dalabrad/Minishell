/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_segments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:36:10 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/05/04 12:12:50 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

void process_single_segment(char *segment, t_tokens **token_ptr, size_t index, char **envp)
{
	size_t segment_tokens = 0;
	token_ptr[index] = check_args_fixed(segment, &segment_tokens, envp);
	if (!token_ptr[index])
		fprintf(stderr, "Warning: could not tokenize segment %zu\n", index);
	else
	{
		set_command_type(token_ptr[index]);
		print_tokens(token_ptr[index]);
	}
	printf("Total tokens checking-process: %zu\n\n", segment_tokens);
}

void process_segments(char **segments, t_tokens **tokens, size_t n, char **envp)
{
	size_t i = 0;
	printf("\n=========== PIPE SEGMENTS ===========\n");
	while (i < n)
	{
		if (!segments[i])
		{
			fprintf(stderr, "Error: pipe_segments[%zu] is NULL\n", i);
			i++;
			continue;
		}
		process_single_segment(segments[i], tokens, i, envp);
		i++;
	}
}