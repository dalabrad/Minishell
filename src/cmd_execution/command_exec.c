/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:38:55 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/10 18:58:20 by dalabrad         ###   ########.fr       */
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
	if (!paths_array)
	{
		free(path_str);
		return ;
	}
	cmd_path = get_cmd_path(args[0], paths_array);
	if (!cmd_path)
	{
		free(path_str);
		free_array(paths_array);
		return ;
	}
	execve(cmd_path, args, NULL);
	free(path_str);
	free_array(paths_array);
	free(cmd_path);
}

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
	non_builtin_exec(args, shell_envp);
	return (EXIT_SUCCESS);
}
