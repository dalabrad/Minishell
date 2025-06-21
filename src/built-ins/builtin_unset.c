/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:54:49 by dalabrad          #+#    #+#             */
/*   Updated: 2025/06/21 16:48:19 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	shell_unset(char **args, t_data *data)
{
	t_env **shell_envp;

	if (!args || !args[0])
		return (EXIT_FAILURE);
	shell_envp = &(data->shell_envp);
	delete_shell_envp_node(shell_envp, args[0]);
	return (EXIT_SUCCESS);
}