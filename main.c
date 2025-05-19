/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:42:59 by dalabrad          #+#    #+#             */
/*   Updated: 2025/05/19 10:57:17 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

// MAIN LOOP CALLING SEGMENTS/PIPES FOR TOKENIZATION AND CONVERSION TO CMD FOR EXEC
static void main_loop(t_data *data)
{
    char *line = data->line;
    char **pipe_segments = data->pipe_segments;
    size_t num_pipes = data->num_pipes;
    t_tokens **tokens_by_segment = data->tokens_by_segment;

    while (1)
    {
        line = readline(PROMPT);
/*         if (is_exit_command(line))
            break; */
        if (!init_pipe_segments(line, &pipe_segments, &num_pipes))
            continue;
        tokens_by_segment = init_tokens_by_segment(num_pipes);
        if (!tokens_by_segment)
        {
            handle_token_alloc_fail(pipe_segments, line);
            continue;
        }
        process_segments(pipe_segments, tokens_by_segment, num_pipes, data);
        execute_pipeline(data);
        free_cmd_list(data->first_cmd);
        data->first_cmd = NULL;
        cleanup(line, pipe_segments, tokens_by_segment, num_pipes);
    }
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
> minishell>> echo "Lola que ase" > out.txt | ls -l | wc -l
>
//PARA PORBAR VALGRIND//
> escribir por Terminal:
> make valgrind
> ./ minishell + ENTER
> minishell>> cat /var/log/.log | grep -i "error" | wc -l | sort -n | head -n 10
*/
