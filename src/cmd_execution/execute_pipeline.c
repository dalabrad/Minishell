/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:23:11 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/24 13:53:20 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static void	one_cmd_pipeline(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->first_cmd;
	if (!cmd)
		return ;
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		printf("minishel: could not fork process\n");
		return ;
	}
	else if (cmd->pid)
	{
		waitpid(cmd->pid, NULL, 0);
	}
	else
	{
		if (cmd->file_in)
			printf("here should redirect input from file\n"); //TO DO!!!
		if (cmd->file_out)
			printf("here should redirect output to file\n"); //TO DO!!!
		command_exec(cmd->args, data);
		exit(0);
	}
}

void	execute_pipeline(t_data *data)
{
	t_cmd	*cmd;
	size_t	i;

	if (data->nbr_cmds == 1)
	{
		one_cmd_pipeline(data);
		return ;
	}
	i = 0;
	cmd = data->first_cmd;
	if (!cmd)
		return ;
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
		{
			if (i > 0)
			{
				close(data->pipes[(i + 1) % 2][R_PIPE]);
				close(data->pipes[(i + 1) % 2][W_PIPE]);
			}
			waitpid(cmd->pid, NULL, 0);
		}
		else
		{
			if (i > 0)
				dup2(data->pipes[(i + 1) % 2][R_PIPE], STDIN_FILENO);
			if (i < (data->nbr_cmds - 1))
				dup2(data->pipes[i % 2][W_PIPE], STDOUT_FILENO);
			if (i > 0)
				close_pipes(data);
			else
			{
				close(data->pipes[0][R_PIPE]);
				close(data->pipes[0][W_PIPE]);
			}
			command_exec(cmd->args, data);
			free_cmd_list(data->first_cmd);
			free_data(data);
			exit(0);
		}
		i++;
		cmd = cmd->next;
	}
}
