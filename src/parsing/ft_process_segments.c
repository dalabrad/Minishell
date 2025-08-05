/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_segments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:36:10 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/08/05 20:25:07 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

// PROCESS ALL PIPES
/* void	process_segments(char **segments, t_tokens **tokens, size_t n,
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
		expand_tokens(tokens[i], data->shell_envp, data->last_status);
		current_cmd = tokens_to_cmd(tokens[i]);
		if (!current_cmd)
		{
			free_tokens_list(tokens[i]);
			tokens[i] = NULL;
			i++;
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
 */

void	process_single_segment(char *segment, t_tokens **token, t_data *data,
		t_cmd **first_cmd)
{
	t_cmd	*current;
	t_cmd	*last;
	size_t	word_count;

	word_count = 0;
	*token = check_args_fixed(segment, &word_count);
	if (!*token)
		return ;
	expand_tokens(*token, data->shell_envp, data->last_status);
	current = tokens_to_cmd(*token);
	if (!current)
	{
		free_tokens_list(*token);
		*token = NULL;
		return ;
	}
	if (!*first_cmd)
		*first_cmd = current;
	else
	{
		last = last_cmd(*first_cmd);
		last->next = current;
	}
}

void	process_segments(char **segments, t_tokens **tokens, size_t n,
		t_data *data)
{
	size_t	i;

	data->first_cmd = NULL;
	i = 0;
	while (i < n)
	{
		process_single_segment(segments[i], &tokens[i], data, &data->first_cmd);
		i++;
	}
	data->nbr_cmds = number_of_cmds(data->first_cmd);
}
