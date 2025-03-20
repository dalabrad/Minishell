/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:08:15 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/20 14:25:54 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	shell_cd(char **args)
{
	extern char	**environ;

	if (!args || !args[0] || !args[1])
		return (EXIT_FAILURE);
	if (!chdir(args[1]))
		printf("Changing directory to %s\n need to udate envp", args[1]);
	return (EXIT_SUCCESS);
}
