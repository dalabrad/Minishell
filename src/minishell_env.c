/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:13:03 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/20 12:18:19 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_exec.h"
#include "../inc/minishell_parsing.h"

int	shell_env(char **args)
{
	extern char	**environ;
	int			i;

	i = 0;
	(void)args;
	if (!environ)
		return (EXIT_FAILURE);
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
