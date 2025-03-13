/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:38:55 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/13 14:15:08 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_exec.h"
#include "../inc/minishell_parsing.h"

static int	shell_exit(char	**args)
{
	(void)args;
	printf("Exiting ./minishel...\n");
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

static int	shell_env(char **args)
{
	extern char	**environ;
	int			i;

	i = 0;
	(void)args;
	if (!environ)
		return (EXIT_FAILURE);
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	shell_echo(char **args)
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

t_builtin	g_builtin[] = {
{.builtin_name = "exit", .foo = shell_exit},
{.builtin_name = "env", .foo = shell_env},
{.builtin_name = "echo", .foo = shell_echo},
{.builtin_name = NULL},
};

void	shell_exec(char **args)
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
