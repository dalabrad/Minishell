/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:13:03 by dalabrad          #+#    #+#             */
/*   Updated: 2025/09/14 23:04:14 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static void print_env_list_safe(t_env *env)
{
	while (env)
	{
		if (env->name && env->name[0] != '\0')
		{
			ft_putstr_fd(env->name, 1);
			ft_putstr_fd("=", 1);
			if (env->value)
				ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
}

int	shell_env(char **args, t_data *data)
{
	(void)args;
	if (!data)
		return (1);

	/* Si la lista está vacía, imprime nada y devuelve 0 (comportamiento bash) */
	print_env_list_safe(data->shell_envp);
	return (0);
}