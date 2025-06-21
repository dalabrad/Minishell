/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:38:55 by dalabrad          #+#    #+#             */
/*   Updated: 2025/06/21 16:47:58 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static char	*absolute_path_case(char **args)
{
	char	*cmd_path;

	if (access(args[0], F_OK | X_OK))
	{
		error_msg_arg(NO_PATH, args[0]);
		return (NULL);
	}
	cmd_path = ft_strdup(args[0]);
	if (!cmd_path)
	{
		error_msg(MALLOC_ERROR);
		return (NULL);
	}
	free(args[0]);
	args[0] = ft_strdup(ft_strrchr(cmd_path, '/') + 1);
	if (!args[0])
	{
		error_msg(MALLOC_ERROR);
		free(cmd_path);
		return (NULL);
	}
	return (cmd_path);
}

static void	non_builtin_exec(char **args, t_env **shell_envp)
{
	char	*cmd_path;

	if (args[0][0] == '/')
		cmd_path = absolute_path_case(args);
	else
		cmd_path = find_path(args, shell_envp);
	if (!cmd_path)
		return ;
	if (execve(cmd_path, args, NULL) == -1)
		free(cmd_path);
}

int	command_exec(char **args, t_data *data)
{
	int			i;
	const char	*current;
	t_env		**shell_envp;

	shell_envp = &(data->shell_envp);
	i = 0;
	while (data->g_builtin[i].name)
	{
		current = data->g_builtin[i].name;
		if (!ft_strncmp(current, args[0], ft_strlen(args[0])))
		{
			if (args[1])
				return (data->g_builtin[i].foo(args + 1, data));
			else
				return (data->g_builtin[i].foo(NULL, data));
		}
		i++;
	}
	non_builtin_exec(args, shell_envp);
	return (EXIT_SUCCESS);
}
