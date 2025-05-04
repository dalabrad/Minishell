/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:38:55 by dalabrad          #+#    #+#             */
/*   Updated: 2025/05/04 18:43:19 by vlorenzo         ###   ########.fr       */
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

static void	execute_cmd(t_tokens *tokens, t_env **shell_envp, char **envp)
{
	char		*path_str;
	char		**paths_array;
	char		*cmd_path;
	char		**args;

	args = tokens_to_args(tokens);
	if (!args)
		return;
	if (handle_redirections(tokens) != 0)
	{
		free_array(args);
		return;
	}
	path_str = get_shell_envp_value(*shell_envp, "PATH");
	if (!path_str)
	{
		error_msg_arg(NO_PATH, args[0]);
		free_array(args);
		return;
	}
	paths_array = get_paths_array(path_str);
	free(path_str);
	if (!paths_array)
		return ;
	cmd_path = get_cmd_path(args[0], paths_array);
	if (cmd_path)
		execve(cmd_path, args, envp);
	free_array(paths_array);
	free(cmd_path);
}

// ENV LEN
static size_t	shell_envp_len(t_env *env)
{
	size_t	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

// ENV NODE=TO_STRING 
char	*env_node_to_str(t_env *node)
{
	char	*temp;
	char	*result;

	if (!node || !node->name || !node->value)
		return (NULL);
	temp = ft_strjoin(node->name, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, node->value);
	free(temp);
	return (result);
}
 // ENV LIST TO ARRAY
char	**env_list_to_array(t_env *env)
{
	size_t	i = 0;
	t_env	*tmp = env;
	size_t	len = shell_envp_len(env);
	char	**array = malloc(sizeof(char *) * (len + 1));

	if (!array)
		return (NULL);
	while (tmp)
	{
		array[i] = env_node_to_str(tmp);
		if (!array[i])
		{
			free_array(array);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

static int is_builtin(char *cmd, t_data data)
{
	int i = 0;
	while (data.g_builtin[i].name)
	{
		if (!ft_strncmp(data.g_builtin[i].name, cmd, ft_strlen(cmd)))
			return i;
		i++;
	}
	return -1;
}

int command_exec_line(char *input, t_data data, char **envp)
{
	t_tokens *tokens;
	char **args;
	int bi;
	int result;
	size_t word_count;

	word_count = 0;

	char **envp_array = env_list_to_array(data.shell_envp);
	tokens = check_args_fixed(input, &word_count, envp_array);

	if (!tokens)
		return EXIT_FAILURE;
	args = tokens_to_args(tokens);
	if (!args)
		return (free_tokens_list(tokens), EXIT_FAILURE);
	bi = is_builtin(args[0], data);
	if (bi >= 0)
	{
		result = data.g_builtin[bi].foo(args + 1, &data.shell_envp);
		free_array(args);
		free_tokens_list(tokens);
		return result;
	}
	execute_cmd(tokens, &data.shell_envp, envp);
	free_array(envp_array);
	free_tokens_list(tokens);
	return EXIT_SUCCESS;
}
