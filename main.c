/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:42:59 by dalabrad          #+#    #+#             */
/*   Updated: 2025/07/03 19:43:50 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"
#include "minishell_signals.h"

//EXIT
int	main_exit(t_data *data)
{
	free_data(data);
	rl_clear_history();
	return data->last_status;
}

// MAIN LOOP CALLING SEGMENTS/PIPES FOR TOKENIZATION AND CONVERSION TO CMD FOR EXEC
void	restore_stdio(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

void	reset_cmd_state(t_data *data, char *line, char **segments,
		t_tokens **tokens)
{
	free_cmd_list(data->first_cmd);
	data->first_cmd = NULL;
	cleanup(line, segments, tokens, 0);
}

static void	main_loop(t_data *data)
{
	t_tokens	**tokens;
	size_t		n_pipe;
	int			in;
	int			out;
	char		*clean;

	char *line, **pipe_seg;
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	if (in < 0 || out < 0)
		return (perror("dup"), (void)0);
	while (1)
	{
		setup_signal_handlers();
		line = readline(PROMPT);
		clean = ft_strtrim(line, "\n");
		free(line);
		line = clean;
		if (is_exit_command(line))
			break ;
		if (!init_pipe_segments(line, &pipe_seg, &n_pipe)
			|| !(tokens = init_tokens_by_segment(n_pipe)))
			continue ;
		process_segments(pipe_seg, tokens, n_pipe, data);
		execute_pipeline(data);
		restore_stdio(in, out);
		reset_cmd_state(data, line, pipe_seg, tokens);
	}
	close(in);
	close(out);
}

// MAIN PARSING ENVP VARIABLES FOR LATER EXPANSION
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	if (argc != 1)
	{
		printf("Too many arguments.\n");
		return (EXIT_FAILURE);
	}
	if (data_init(&data, envp)) // Pasamos envp a t_data
	{
		printf("Failed to initialize data\n");
		return (EXIT_FAILURE);
	}
	main_loop(&data);
	return (main_exit(&data));  // Devuelve data->last_status y libera memoria
}

/*
//PARA PROBAR MINISHELL//
> escribir por Terminal:
> make
> ./minishell + ENTER
> tokens
>
//PARA PORBAR VALGRIND//
> escribir por Terminal:
> make valgrind
> ./ minishell + ENTER
> minishell>> cat /var/log/.log | grep -i "error" | wc -l | sort -n | head -n 10
*/
