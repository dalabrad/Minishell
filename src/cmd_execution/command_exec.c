/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:38:55 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/25 18:14:32 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_exec.h"
#include "../inc/minishell_parsing.h"

t_builtin	g_builtin[] = {
{.builtin_name = "exit", .foo = shell_exit},
{.builtin_name = "env", .foo = shell_env},
{.builtin_name = "echo", .foo = shell_echo},
{.builtin_name = "pwd", .foo = shell_pwd},
{.builtin_name = "cd", .foo = shell_cd},
{.builtin_name = "export", .foo = shell_export},
{.builtin_name = "unset", .foo = shell_unset},
{.builtin_name = NULL},
};

int	command_exec(char **args, t_env **shell_envp)
{
	int			i;
	const char	*current;

	i = 0;
	while (g_builtin[i].builtin_name)
	{
		current = g_builtin[i].builtin_name;
		if (!ft_strncmp(current, args[0], ft_strlen(args[0])))
		{
			printf("Executing built-in %s\n", args[0]);
			return (g_builtin[i].foo(args + 1, shell_envp));
		}
		i++;
	}
	printf("Aqui deberian implementarse los comandos de execve(%s)\n", args[0]);
	return (EXIT_SUCCESS);
}
