/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:15:13 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/07/28 19:31:58 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"
#include "minishell_exec.h"

// EXIT COMMAND
int is_exit_command(char **line, t_data *data)
{
	if (ft_strcmp(line[0], "exit") == 0)
	{
		shell_exit(line, data);
		return (1);
	}
	return (0);
}

// CLEAN STRUCT T_PIPES
t_pipes	*clean_struct(t_pipes *args)
{
	t_pipes	*temp;

	temp = NULL;
	while (args->next)
	{
		temp = args;
		args = args->next;
		free(temp);
		temp = NULL;
	}
	return (temp);
}

// FREE TOKENS
void	free_tokens_list(t_tokens *head)
{
	t_tokens *tmp;

	while (head && head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->str);
		free(tmp);
	}
}

// CLEAN-UP SEGMENTS/TOKENIZED-ARGS ARRAY
void cleanup(char **segments, t_tokens **tokens, size_t n)
{
	free_array(segments);
	if (tokens)
	{
		size_t j = 0;
		while (j < n)
			free_tokens_list(tokens[j++]);
		free(tokens);
	}
}
