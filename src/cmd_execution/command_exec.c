/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:38:55 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/22 20:12:50 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

/* t_builtin	g_builtin[] = {
{.name = "exit", .foo = shell_exit},
{.name = "env", .foo = shell_env},
{.name = "echo", .foo = shell_echo},
{.name = "pwd", .foo = shell_pwd},
{.name = "cd", .foo = shell_cd},
{.name = "export", .foo = shell_export},
{.name = "unset", .foo = shell_unset},
{.name = NULL},
}; */

static char	**get_paths_array(char *path_str)
{
	char		**paths;

	paths = ft_split(path_str, ':');
	if (!paths)
	{
		error_msg(MALLOC_ERROR);
		return (NULL);
	}
	return (paths);
}

static char	*get_cmd_path(char	*cmd, char **paths)
{
	char	*tmp;
	char	*cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!cmd_path)
		{
			error_msg(MALLOC_ERROR);
			return (NULL);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	error_msg_arg(CMD_NOT_FOUND, cmd);
	return (NULL);
}

static void	non_builtin_exec(char **args, t_env **shell_envp)
{
	char		*path_str;
	char		**paths_array;
	char		*cmd_path;

	path_str = get_shell_envp_value(*shell_envp, "PATH");
	if (!path_str)
	{
		error_msg_arg(NO_PATH, args[0]);
		return ;
	}
	paths_array = get_paths_array(path_str);
	free(path_str);
	if (!paths_array)
		return ;
	cmd_path = get_cmd_path(args[0], paths_array);
	if (!cmd_path)
	{
		free_array(paths_array);
		return ;
	}
	if (execve(cmd_path, args, NULL) == -1)
	{
		free_array(paths_array);
		free(cmd_path);
	}
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
			fprintf(stderr, "Executing built-in %s\n", args[0]);
			return (data->g_builtin[i].foo(args + 1, shell_envp));
		}
		i++;
	}
	fprintf(stderr, "Executing command %s\n", args[0]);
	non_builtin_exec(args, shell_envp);
	return (EXIT_SUCCESS);
}
