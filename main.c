/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:42:59 by dalabrad          #+#    #+#             */
/*   Updated: 2025/07/28 20:18:59 by vlorenzo         ###   ########.fr       */
/*   Updated: 2025/07/28 21:38:54 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"
#include "minishell_signals.h"

// MAIN LOOP CALLING SEGMENTS/PIPES FOR TOKENIZATION
void	restore_stdio(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

static void	process_input_line(char *line, t_data *data, int in, int out)
{
	char		**pipe_seg;
	t_tokens	**tokens;
	size_t		n_pipe;
	HIST_ENTRY	**entries;

	if (!line || !*line)
		return ;
	add_history(line);
	if (ft_strcmp(line, "history") == 0)
	{
		entries = history_list();
		if (entries)
		{
			for (int i = 0; entries[i]; i++)
				printf("%d: %s\n", i + history_base, entries[i]->line);
		}
		return ;
	}
	if (!init_pipe_segments(line, &pipe_seg, &n_pipe)
		|| !(tokens = init_tokens_by_segment(n_pipe)))
		return ;
	process_segments(pipe_seg, tokens, n_pipe, data);
	execute_pipeline(data);
	restore_stdio(in, out);
	reset_cmd_state(data, line, pipe_seg, tokens);
}

void	reset_cmd_state(t_data *data, char *line, char **segments,
		t_tokens **tokens)
{
	(void)*line;
	free_cmd_list(data->first_cmd);
	data->first_cmd = NULL;
	cleanup(segments, tokens, 0);
}

static void	main_loop(t_data *data)
{
	char	*line;
	int		in;
	int		out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	if (in < 0 || out < 0)
		return (perror("dup"), (void)0);
	read_history(".minishell_history");
	while (1)
	{
		setup_signal_handlers();
		line = readline(PROMPT);
		if (!line || is_exit_command(&line, data))
			break ;
		process_input_line(line, data, in, out);
		if (line)
			free(line);
	}
	write_history(".minishell_history");
	rl_clear_history();
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
	if (data_init(&data, envp))
	{
		printf("Failed to initialize data\n");
		return (EXIT_FAILURE);
	}
	main_loop(&data);
	free_data(&data);
	return (EXIT_SUCCESS);
}
