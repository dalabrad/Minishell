/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:23:11 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/22 21:07:45 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

void	execute_pipeline(t_data *data)
{
	t_cmd	*cmd;
	size_t	i;

	i = 0;
	cmd = data->first_cmd;
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
			printf("minishel: could not fork process\n");
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
			if (i < data->nbr_cmds - 1)
				dup2(data->pipes[i % 2][W_PIPE], STDOUT_FILENO);
			if (i > 0)
				close_pipes(data);
			else
			{
				close(data->pipes[0][0]);
				close(data->pipes[0][1]);
			}
			command_exec(cmd->args, data);
			exit(1);
		}
		i++;
		cmd = cmd->next;
	}
}
