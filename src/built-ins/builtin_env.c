/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:13:03 by dalabrad          #+#    #+#             */
/*   Updated: 2025/06/21 16:50:11 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	shell_env(char **args, t_data *data)
{
	t_env	*env;

	(void)args;
	env = data->shell_envp;
	while (env)
	{
		if (env->value) // printea si hay valor
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

/* int	shell_env(char **args, t_data *data)
{
	t_env	**shell_envp;

	shell_envp = &(data->shell_envp);
	(void)args;
	if (!shell_envp || !(*shell_envp))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
 */