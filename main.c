/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:42:59 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/15 19:24:40 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static void main_loop(void)
{
	char *line;
	char **pipe_segments;
	size_t i_pipes;
	t_tokens **tokens_by_segment;

	while (1)
	{
		line = readline(PROMPT);
		if (is_exit_command(line))
			break;
		if (!init_pipe_segments(line, &pipe_segments, &i_pipes))
			continue;
		tokens_by_segment = init_tokens_by_segment(i_pipes);
		if (!tokens_by_segment)
		{
			free_array(pipe_segments);
			free(line);
			continue;
		}
		process_segments(pipe_segments, tokens_by_segment, i_pipes);
		cleanup(line, pipe_segments, tokens_by_segment, i_pipes);
	}
}
			
int main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	if (argc != 1)
		return (printf("Too many arguments or readline failure.\n"), 0);
	main_loop();
	return (0);
}
