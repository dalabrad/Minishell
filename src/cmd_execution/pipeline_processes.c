/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:18:35 by dalabrad          #+#    #+#             */
/*   Updated: 2025/07/28 18:16:13 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

void	parent_process(t_data *data, t_cmd *cmd, size_t i)
{
	int	status;

	if (i > 0)
	{
		close(data->pipes[(i + 1) % 2][R_PIPE]);
		close(data->pipes[(i + 1) % 2][W_PIPE]);
	}
	status = 0;
	waitpid(cmd->pid, &status, 0);
	if (WIFEXITED(status))
		data->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->last_status = 128 + WTERMSIG(status);
}

void	child_process(t_data *data, t_cmd *cmd, size_t i)
{
	if (i > 0)
		dup2(data->pipes[(i + 1) % 2][R_PIPE], STDIN_FILENO);
	if (i < (data->nbr_cmds - 1))
		dup2(data->pipes[i % 2][W_PIPE], STDOUT_FILENO);
	if (cmd->file_in)
	{
		file_in_redir(cmd);
	}
	if (cmd->file_out)
	{
		file_out_redir(cmd);
	}
	close_pipes(data);
	command_exec(cmd->args, data);
	free_cmd_list(data->first_cmd);
	free_data(data);
	exit(EXIT_SUCCESS);
}
