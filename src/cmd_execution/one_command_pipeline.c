/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:26:53 by dalabrad          #+#    #+#             */
/*   Updated: 2025/07/22 20:40:10 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

void	one_cmd_pipeline(t_data *data)
{
    t_cmd	*cmd = data->first_cmd;
    int     fd_in, fd_out;

    if (!cmd)
        return;
    if (is_builtin(cmd->args[0], data))
        data->last_status = command_exec(cmd->args, data);
    else
    {
        cmd->pid = fork();
		if (cmd->pid == -1)
		{
			error_msg(FORK_ERROR);
			return;
		}
        if (cmd->pid)
            waitpid(cmd->pid, &data->last_status, 0);
        else
        {
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
            command_exec(cmd->args, data);
            free_cmd_list(data->first_cmd);
            free_data(data);
            exit(EXIT_SUCCESS);
        }
    }
}
