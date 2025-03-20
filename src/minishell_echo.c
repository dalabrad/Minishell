/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:10:22 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/20 14:25:43 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	shell_echo(char **args)
{
	int		i;
	bool	nl_flag;

	i = 1;
	nl_flag = true;
	if (!args || !args[0])
		return (EXIT_FAILURE);
	if (args[i] && !ft_strncmp("-n", args[i], ft_strlen(args[i])))
	{
		nl_flag = false;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (nl_flag)
		printf("\n");
	return (EXIT_SUCCESS);
}
