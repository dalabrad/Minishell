/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:15:03 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/03 15:03:38 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

size_t	array_size(char **array)
{
	size_t	size;

	size = 0;
	while (array[size])
		size++;
	return (size);
}

void	print_array(char **array)
{
	size_t	i;

	if (!array || !*array)
		return ;
	i = 0;
	while (array[i])
	{
		printf("[%zu] : %s\n", i, array[i]);
		i++;
	}
}
