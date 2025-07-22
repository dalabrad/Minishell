/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:38:55 by dalabrad          #+#    #+#             */
/*   Updated: 2025/07/20 19:11:45 by dalabrad         ###   ########.fr       */
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

static int	non_builtin_exec(char **args, t_env **shell_envp)
{
	char		*cmd_path;
	char		**envp;

	if (args[0][0] == '/')
		cmd_path = absolute_path_case(args);
	else
		cmd_path = find_path(args, shell_envp);
	if (!cmd_path)
		exit (127);
	envp = shell_envp_array_create(*shell_envp);
	if (!envp)
	{
		free(cmd_path);
		return(EXIT_FAILURE);
	}
	if (execve(cmd_path, args, envp) == -1)
	{
		free(cmd_path);
		free_array(envp);
		exit(2);
		return (2);
	}
	return (EXIT_SUCCESS);
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
			return (data->g_builtin[i].foo(args + 1, data));
		}
		i++;
	}
	return (non_builtin_exec(args, shell_envp));
}
