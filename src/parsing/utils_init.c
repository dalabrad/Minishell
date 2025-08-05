/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:51:46 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/08/05 19:22:37 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	handle_token_alloc_fail(char **segments, char *line)
{
	free_array(segments);
	free(line);
	return (0);
}

t_pipes	*init_struct(t_pipes *args)
{
	args = malloc(sizeof(t_pipes));
	if (!args)
		return (NULL);
	args->index = 0;
	args->str = NULL;
	args->next = NULL;
	return (args);
}

int	init_pipe_segments(char *line, char ***segments, size_t *n)
{
	*segments = ft_minisplit(line, '|', n);
	if (!*segments)
		return (0);
	return (1);
}

t_tokens	**init_tokens_by_segment(size_t count)
{
	t_tokens	**arr;
	size_t		i;

	arr = malloc(sizeof(t_tokens *) * (count + 1));
	if (!arr)
	{
		perror("malloc tokens_by_segment");
		return (NULL);
	}
	i = 0;
	while (i <= count)
		arr[i++] = NULL;
	return (arr);
}

void	print_history(void)
{
	HIST_ENTRY	**entries;
	int			i;

	entries = history_list();
	if (!entries)
		return ;
	i = 0;
	while (entries[i])
	{
		printf("%d: %s\n", i + history_base, entries[i]->line);
		i++;
	}
}
