/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:26:53 by dalabrad          #+#    #+#             */
/*   Updated: 2025/05/10 12:34:12 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

void	one_cmd_pipeline(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->first_cmd;
	if (!cmd)
		return ;
	if (is_builtin(cmd->args[0], data))
	{
		command_exec(cmd->args, data);
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
		waitpid(cmd->pid, NULL, 0);
	}
	else
	{
		if (cmd->file_in)
			printf("here should redirect input from file\n"); //TO DO!!!
		if (cmd->file_out)
			printf("here should redirect output to file\n"); //TO DO!!!
		command_exec(cmd->args, data);
		free_cmd_list(data->first_cmd);
		free_data(data);
		exit(0);
	}
}
