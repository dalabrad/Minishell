/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env_to_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:46:34 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/08/04 20:03:20 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

/*
 * Convierte la lista enlazada de variables de entorno (t_env)
 * en un array de strings tipo "NAME=VALUE" para pasar a execve.
 */

 char *ft_strjoin_3(const char *s1, const char *s2, const char *s3)
{
	char *tmp = ft_strjoin(s1, s2);
	char *res = ft_strjoin(tmp, s3);
	free(tmp);
	return res;
}

char **shell_envp_to_array(t_env *env)
{
	char	**array;
	int		count = 0;
	int		i = 0;
	t_env	*tmp = env;

	// Contar elementos visibles
	while (tmp)
	{
		if (tmp->visible)
			count++;
		tmp = tmp->next;
	}

	printf("%d\n", count);

	array = ft_calloc(count + 1, sizeof(char *));
	if (!array)
		return (NULL);
	
	tmp = env;
	while (tmp)
	{
		if (tmp->visible)
		{
			array[i] = ft_strjoin_3(tmp->name, "=", tmp->value);
			if (!array[i++])
			{
				free_array(array);
				return (NULL);
			}
		}
		tmp = tmp->next;
	}
	printf("%s\n", array[0]);

	return (array);
}
