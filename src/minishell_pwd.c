/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:21:38 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/20 14:16:55 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	shell_pwd(char **args)
{
	char	*directory;

	directory = NULL;
	if (!args || !args[0])
		return (EXIT_FAILURE);
	directory = getcwd(NULL, 0);
	if (!directory)
		return (printf("Error in getcwd()\n"));
	printf("%s\n", directory);
	free(directory);
	return (EXIT_SUCCESS);
}
