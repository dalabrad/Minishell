/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:38:55 by dalabrad          #+#    #+#             */
/*   Updated: 2025/06/27 19:50:40 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static char *absolute_path_case(char **args)
{
	char *cmd_path;

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

static void non_builtin_exec(char **args, t_data *data)
{
	char *cmd_path;
	char **envp = shell_envp_to_array(data->shell_envp);

	if (args[0][0] == '/')
		cmd_path = absolute_path_case(args);
	else
		cmd_path = find_path(args, &data->shell_envp);
	if (!cmd_path)
	{
		free_array(envp);
		return ;
	}
	execve(cmd_path, args, envp);
	free(cmd_path);
	free_array(envp);
	exit(127);
}

int command_exec(char **args, t_data *data)
{
	int i;
	const char *current;

	i = 0;
	while (data->g_builtin[i].name)
	{
		current = data->g_builtin[i].name;
		if (!ft_strncmp(current, args[0], ft_strlen(args[0]))
			&& ft_strlen(current) == ft_strlen(args[0]))
		{
			int res;
			if (args[1])
				res = data->g_builtin[i].foo(args + 1, data);
			else
				res = data->g_builtin[i].foo(NULL, data);
			return (res);
		}
		i++;
	}
	non_builtin_exec(args, data);
	return (EXIT_SUCCESS);
}
