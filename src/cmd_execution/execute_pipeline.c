/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:23:11 by dalabrad          #+#    #+#             */
/*   Updated: 2025/07/03 20:23:25 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static void	parent_process(t_data *data, t_cmd *cmd, size_t i)
{
	if (i > 0)
	{
		close(data->pipes[(i + 1) % 2][R_PIPE]);
		close(data->pipes[(i + 1) % 2][W_PIPE]);
	}
	waitpid(cmd->pid, NULL, 0);
}

static void	child_process(t_data *data, t_cmd *cmd, size_t i)
{
	int fd_in, fd_out;
	if (i > 0)
		dup2(data->pipes[(i + 1) % 2][R_PIPE], STDIN_FILENO);
	if (i < (data->nbr_cmds - 1))
		dup2(data->pipes[i % 2][W_PIPE], STDOUT_FILENO);
	if (cmd->file_in)
	{
		fd_in = open(cmd->file_in, O_RDONLY);
		if (fd_in < 0)
			exit(error_msg_arg(NO_PATH, cmd->file_in));
		if (dup2(fd_in, STDIN_FILENO) < 0)
			exit(error_msg(DUP2_ERROR));
		close(fd_in);
	}
	if (cmd->file_out)
	{
		if (cmd->append_out)
			fd_out = open(cmd->file_out, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd_out = open(cmd->file_out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out < 0)
			exit(error_msg_arg(NO_PATH, cmd->file_out));
		if (dup2(fd_out, STDOUT_FILENO) < 0)
			exit(error_msg(DUP2_ERROR));
		close(fd_out);
	}
	close_pipes(data);
	command_exec(cmd->args, data);
	free_cmd_list(data->first_cmd);
	free_data(data);
	exit(EXIT_SUCCESS);
}

static void	cmd_loop(t_data *data, t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd && i < data->nbr_cmds)
	{
		if (pipe(data->pipes[i % 2]) == -1)
		{
			error_msg(PIPE_ERROR);
			return ;
		}
		cmd->pid = fork();
		if (cmd->pid == -1)
		{
			error_msg(FORK_ERROR);
			return ;
		}
		else if (cmd->pid)
			parent_process(data, cmd, i);
		else
			child_process(data, cmd, i);
		i++;
		cmd = cmd->next;
	}
}

void	execute_pipeline(t_data *data)
{
	t_cmd	*cmd;

	printf("execute_pipeline, OUT\n");
	if (data->nbr_cmds == 1)
	{
		printf("execute_pipeline, IN\n");
		one_cmd_pipeline(data);
		return ;
	}
	cmd = data->first_cmd;
	if (!cmd)
		return ;
	cmd_loop(data, cmd);
}
