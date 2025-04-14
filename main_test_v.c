/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_v.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:58:00 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/04/11 18:20:58 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "minishell_exec.h" */
#include "inc/minishell_parsing.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str_exit = "exit";
	char	*line;
	char	**pipe_segments;
	size_t	i_pipes;
	size_t	i;
	t_tokens **tokens_by_segment;

	(void)argv;
	(void)envp;

	if (argc != 1)
	{
		return (printf("Too many arguments or readline failure.\n"), 0);
	}
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (!ft_strcmp(line, str_exit))
		{
			free(line);
			break;
		}

		pipe_segments = ft_minisplit(line, '|', &i_pipes);
		if (!pipe_segments)
		{
			free(line);
			continue;
		}

		tokens_by_segment = malloc(sizeof(t_tokens *) * (i_pipes + 1));
		if (!tokens_by_segment)
		{
			perror("malloc tokens_by_segment");
			free_array2(pipe_segments);
			free(line);
			continue;
		}

		for (size_t i = 0; i < i_pipes; i++)
			tokens_by_segment[i] = NULL;

		printf("\n=========== PIPE SEGMENTS ===========\n");
		i = 0;
		while (i < i_pipes)
		{
			if (!pipe_segments[i])
			{
				fprintf(stderr, "Error: pipe_segments[%zu] is NULL\n", i);
				tokens_by_segment[i] = NULL;
				i++;
				continue;
			}

			size_t segment_tokens = 0;
			tokens_by_segment[i] = check_args_fixed(pipe_segments[i], &segment_tokens);
			if (!tokens_by_segment[i])
			{
				fprintf(stderr, "Warning: could not tokenize segment %zu\n", i);
			}
			else
			{
				// FIRST ARG AS COMMAND
				set_command_type(tokens_by_segment[i]);
				print_tokens(tokens_by_segment[i]);
			}
			printf("Total tokens checking-process: %zu\n\n", segment_tokens);
			i++;
		}

		free_array2(pipe_segments);
		if (tokens_by_segment)
		{
			for (size_t j = 0; j < i_pipes; j++)
				if (tokens_by_segment[j])
					free_tokens_list(tokens_by_segment[j]);
			free(tokens_by_segment);
		}
		free(line);
	}
	return (0);
}

/*
> PARA PROBAR:
>
> make testv
> ./minishell + ENTER
> minishell>> echo "Lola que ase" >> out.txt | ls .l | wc -l
*/
