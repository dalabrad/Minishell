/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 00:29:51 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/05/26 00:29:53 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"
#include <unistd.h>
#include <stdio.h>

void	restore_stdio(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

void	reset_cmd_state(t_data *data, char *line, char **segments, t_tokens **tokens)
{
	free_cmd_list(data->first_cmd);
	data->first_cmd = NULL;
	cleanup(line, segments, tokens, 0); // <- Asegúrate de que cleanup acepta n = 0 sin fallar
}

int	ini_pipe(char *line, char ***pipe_segments, size_t *n_pipe)
{
	return init_pipe_segments(line, pipe_segments, n_pipe);
}

t_tokens **ini_tokens(size_t n_pipe)
{
	return init_tokens_by_segment(n_pipe);
}
