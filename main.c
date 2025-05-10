/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:42:59 by dalabrad          #+#    #+#             */
/*   Updated: 2025/05/10 15:53:22 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

// MAIN LOOP PASING ENVP VARIABLES FOR LATER EXPANSION
static void main_loop(char **envp, int fd, char *line)
{
	char **pipe_segments;
	size_t i_pipes;
	t_tokens **tokens_by_segment;

	while (1)
	{
		dup2(fd, STDIN_FILENO);
		line = readline(PROMPT);
		if (is_exit_command(line))
		{
			rl_clear_history(); // limpia el historial de readline
			break;
		}
		if (!init_pipe_segments(line, &pipe_segments, &i_pipes))
			continue;
		tokens_by_segment = init_tokens_by_segment(i_pipes);
		if (!tokens_by_segment)
		{
			free_array(pipe_segments);
			free(line);
			continue;
		}
		process_segments(pipe_segments, tokens_by_segment, i_pipes, envp);
		cleanup(line, pipe_segments, tokens_by_segment, i_pipes);
	}
}

// MAIN FUNCTION
int main(int argc, char **argv, char **envp)
{
	(void)argv;
	t_data	data;
	int fd;
	char *line;

	// CHECK SIGNALS un dia de estos
	if (argc != 1)
		return (printf("Too many arguments or readline failure.\n"), 0);
	line = NULL;
	fd = dup(STDIN_FILENO);
/* 	if (data_init(&data, envp))
		return (EXIT_FAILURE); */
	main_loop(envp, fd, line);
	return (0);
}

/*
//PARA PROBAR MINISHELL//
> escribir por Terminal:
> make 
> ./minishell + ENTER
> minishell>> echo "Lola que ase" > out.txt | ls -l | wc -l
>
//PARA PORBAR VALGRIND//
> escribir por Terminal:
> make valgrind
> ./ minishell + ENTER
> minishell>> cat /var/log/.log | grep -i "error" | wc -l | sort -n | head -n 10
*/
