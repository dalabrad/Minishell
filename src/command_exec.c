/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:38:55 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/20 14:12:31 by dalabrad         ###   ########.fr       */
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
{.builtin_name = NULL},
};

void	command_exec(char **args)
{
	int			i;
	const char	*current;

	i = 0;
	while (g_builtin[i].builtin_name)
	{
		current = g_builtin[i].builtin_name;
		if (!ft_strncmp(current, args[0], ft_strlen(args[0])))
		{
			g_builtin[i].foo(args);
			return ;
		}
		i++;
	}
	printf("Aqui deberian implementarse los comandos de execve(%s)\n", args[0]);
}
