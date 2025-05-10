/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_segments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:36:10 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/05/10 16:26:49 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

void process_single_segment(char *segment, t_tokens **token_ptr, size_t index)
{
	size_t segment_tokens = 0;
	token_ptr[index] = check_args_fixed(segment, &segment_tokens);
	if (!token_ptr[index])
		fprintf(stderr, "Warning: could not tokenize segment %zu\n", index);
	else
	{
		set_command_type(token_ptr[index]);
		print_tokens(token_ptr[index]);
	}
	// Pronto: pasar los TOKENS por segmento a EXEC
	/* 		
	if (create_cmds(&data, argc - 1, argv + 1))
		return (EXIT_FAILURE); 
		execute_pipeline(&data);
		free_cmd_list(data.first_cmd);
		free_data(&data);
	*/
	printf("Total tokens checking-process: %zu\n\n", segment_tokens);
}

void process_segments(char **segments, t_tokens **tokens, size_t n)
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
		process_single_segment(segments[i], tokens, i);
		i++;
	}
}