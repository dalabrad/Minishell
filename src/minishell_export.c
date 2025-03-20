/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:20:39 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/20 14:34:19 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	shell_export(char **args)
{
	extern char	**environ;
	int			i;
	int			name_len;

	if (!args || !args[0] || !args[1] || !ft_strchr(args[1], '='))
		return (EXIT_FAILURE);
	i = 0;
	name_len = ft_strchr(args[1], '=') - &args[1][0];
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], args[1], name_len))
		{
			environ[i] = ft_strdup(args[1]);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	i = 0;
	while (i < MAX_ENV)
	{
		if (!environ[i])
		{
			environ[i] = ft_strdup(args[1]);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
