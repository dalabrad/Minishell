/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:54:49 by dalabrad          #+#    #+#             */
/*   Updated: 2025/05/19 17:12:37 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	shell_unset(char **args, t_data *data)
{
	t_env	**shell_envp;
	size_t	i;

	if (!args || !args[0])
		return (EXIT_FAILURE);
	shell_envp = &(data->shell_envp);
	i = 0;
	while (args[i])
	{
		delete_shell_envp_node(shell_envp, args[0]);
		i++;
	}
	return (EXIT_SUCCESS);
}
