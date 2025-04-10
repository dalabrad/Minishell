/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_initClean.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:51:46 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/04/09 21:44:39 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "minishell_exec.h" */
#include "../inc/minishell_parsing.h"

// INIT STRUCT T_PIPES
t_pipes	*init_struct(t_pipes *args)
{
	args = malloc(sizeof(t_pipes));
	if (!args)
		return (NULL);
	args->index = 0;
	args->str = NULL;
	args->next = NULL;
	free(args);
	return (args);
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

// FREE ARRAY DUH
void	**free_array2(char **array)
{
	int	limit;

	limit = 0;
	while (array[limit] != 0)
	{
		free(array[limit]);
		array[limit] = NULL;
		limit++;
	}
	free(array);
	array = NULL;
	return (0);
}
