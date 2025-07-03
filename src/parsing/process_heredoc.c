/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:21:53 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/07/03 19:20:32 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int process_heredoc(t_cmd *cmd)
{
	int		pipefd[2];
	char	*line;

	if (!cmd->heredoc_delimiter)
		return (0);
	if (pipe(pipefd) == -1)
		return (error_msg(PIPE_ERROR));
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, cmd->heredoc_delimiter) == 0)
			break;
		ft_putstr_fd(line, pipefd[1]);
		ft_putchar_fd('\n', pipefd[1]);
		free(line);
	}
	free(line);
	close(pipefd[1]);
	cmd->heredoc_fd = pipefd[0];
	return (0);
}

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
		return (error_msg(MALLOC_ERROR), NULL);
	free(args[0]);
	args[0] = ft_strdup(ft_strrchr(cmd_path, '/') + 1);
	if (!args[0])
		return (free(cmd_path), error_msg(MALLOC_ERROR), NULL);
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
		return (free_array(envp));
	execve(cmd_path, args, envp);
	free(cmd_path);
	free_array(envp);
	exit(127);
}

int command_exec(char **args, t_data *data)
{
	int i = 0;

	while (data->g_builtin[i].name)
	{
		if (!ft_strncmp(data->g_builtin[i].name, args[0], ft_strlen(args[0]))
			&& ft_strlen(data->g_builtin[i].name) == ft_strlen(args[0]))
			return (data->g_builtin[i].foo(args + 1, data));
		i++;
	}
	non_builtin_exec(args, data);
	return (EXIT_SUCCESS);
}

