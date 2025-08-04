/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:23:11 by dalabrad          #+#    #+#             */
/*   Updated: 2025/07/28 17:19:31 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

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

	if (data->nbr_cmds == 1)
	{
		one_cmd_pipeline(data);
		return ;
	}
	cmd = data->first_cmd;
	if (!cmd)
		return ;
	cmd_loop(data, cmd);
}
