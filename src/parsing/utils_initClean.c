/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_initClean.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:51:46 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/04/11 13:58:51 by vlorenzo         ###   ########.fr       */
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
	while (array && array[limit])
	{
		free(array[limit]);
		array[limit] = NULL;
		limit++;
	}
	free(array);
	array = NULL;
	return (0);
}
// FREE TOKENS
void	free_tokens_list(t_tokens *head)
{
	t_tokens *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->str);
		free(tmp);
	}
}