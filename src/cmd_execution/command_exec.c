/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:38:55 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/10 17:45:49 by dalabrad         ###   ########.fr       */
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

static char	*get_cmd_path(char	*cmd, char *path_str)
{
	char	**paths;
	char	*tmp;
	char	*cmd_path;
	int		i;

	paths = get_paths_array(path_str);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!cmd_path)
		{
			free_array(paths);
			error_msg(MALLOC_ERROR);
			return (NULL);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free_array(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_array(paths);
	error_msg_arg(CMD_NOT_FOUND, cmd);
	return (NULL);
}

int	command_exec(char **args, t_env **shell_envp)
{
	int			i;
	const char	*current;
	char		*path_str;
	char		*cmd_path;

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
	// No built-in command execution implementation
	path_str = get_shell_envp_value(*shell_envp, "PATH");
	if (!path_str)
	{
		error_msg_arg(NO_PATH, args[0]);
		return (EXIT_FAILURE);
	}
	cmd_path = get_cmd_path(args[0], path_str);
	if (!cmd_path)
	{
		free(path_str);
		return (EXIT_FAILURE);
	}
	printf("here execve() should be executed\n");
	//execve(cmd_path, args, NULL);
	printf("path_str : %s\n", path_str);
	printf("cmd_path : %s\n", cmd_path);
	printf("cmd_array:\n");
	print_array(args);
	free(path_str);
	free(cmd_path);
	return (EXIT_SUCCESS);
}
