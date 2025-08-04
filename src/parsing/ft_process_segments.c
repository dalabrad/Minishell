/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_segments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:36:10 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/08/04 18:13:44 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

// PROCESS ALL PIPES
void	process_segments(char **segments, t_tokens **tokens, size_t n,
		t_data *data)
{
	size_t	i;
	t_cmd	*current_cmd;
	t_cmd	*last;
	size_t	word_count;

	data->first_cmd = NULL;
	i = 0;
	while (i < n)
	{
		word_count = 0;
		tokens[i] = check_args_fixed(segments[i], &word_count);
		if (!tokens[i])
		{
			i++;
			continue ;
		}
		// Expande variables en tokens
		expand_tokens(tokens[i], data->shell_envp, data->last_status);
		current_cmd = tokens_to_cmd(tokens[i]);
		if (!current_cmd)
		{
			i++; // Libera tokens[i], incluyendo token->str (doble free?)
			continue ;
		}
		if (!data->first_cmd)
			data->first_cmd = current_cmd;
		else
		{
			last = last_cmd(data->first_cmd);
			last->next = current_cmd;
		}
		i++;
	}
	data->nbr_cmds = number_of_cmds(data->first_cmd);
}
