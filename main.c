/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:42:59 by dalabrad          #+#    #+#             */
/*   Updated: 2025/05/26 00:18:00 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"
#include "minishell_signals.h"

// MAIN LOOP CALLING SEGMENTS/PIPES FOR TOKENIZATION AND CONVERSION TO CMD FOR EXEC
static void restore_stdio(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

static void reset_cmd_state(t_data *data, char *line,
	char **segments, t_tokens **tokens)
{
	free_cmd_list(data->first_cmd);
	data->first_cmd = NULL;
	cleanup(line, segments, tokens, 0);
}

static void main_loop(t_data *data)
{
	char *line, **pipe_seg;
	t_tokens **tokens;
	size_t n_pipe;
	int in;
	int out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);

	if (in < 0 || out < 0)
		return (perror("dup"), (void)0);
	while (1)
	{
        setup_signal_handlers();
		line = readline(PROMPT);
		if (is_exit_command(line))
			break;
		if (!ini_pipe(line, &pipe_seg, &n_pipe) || !(tokens = ini_tokens(n_pipe)))
			continue;
		process_segments(pipe_seg, tokens, n_pipe, data);
		execute_pipeline(data);
		restore_stdio(in, out);
		reset_cmd_state(data, line, pipe_seg, tokens);
	}
	close(in);
	close(out);
}

// MAIN PARSING ENVP VARIABLES FOR LATER EXPANSION
int main(int argc, char **argv, char **envp)
{
    (void)argv;
	t_data data;

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
    free_data(&data);
    return (EXIT_SUCCESS);
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
