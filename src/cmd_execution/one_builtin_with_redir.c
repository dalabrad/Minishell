/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_builtin_with_redir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:05:30 by dalabrad          #+#    #+#             */
/*   Updated: 2025/07/28 19:24:28 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static int	file_in_redir_builtin(t_cmd *cmd)
{
	int	fd_in;

	fd_in = open(cmd->file_in, O_RDONLY);
	if (fd_in < 0)
		return (error_msg_arg(NO_PATH, cmd->file_in));
	if (dup2(fd_in, STDIN_FILENO) < 0)
	{
		close(fd_in);
		return (error_msg(DUP_ERROR));
	}
	close(fd_in);
	return (0);
}

static int	file_out_redir_builtin(t_cmd *cmd)
{
	int	fd_out;

	if (cmd->append_out)
		fd_out = open(cmd->file_out, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd_out = open(cmd->file_out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out < 0)
		return (error_msg_arg(NO_PATH, cmd->file_out));
	if (dup2(fd_out, STDOUT_FILENO) < 0)
	{
		close(fd_out);
		return (error_msg(DUP_ERROR));
	}
	close(fd_out);
	return (0);
}

static void	redir_restore(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

void	one_builtin_with_redir(t_data *data, t_cmd *cmd)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
	{
		error_msg(DUP_ERROR);
		data->last_status = 1;
		return ;
	}
	if (cmd->file_in && file_in_redir_builtin(cmd) < 0)
	{
		redir_restore(saved_stdin, saved_stdout);
		data->last_status = 1;
		return ;
	}
	if (cmd->file_out && file_out_redir_builtin(cmd) < 0)
	{
		redir_restore(saved_stdin, saved_stdout);
		data->last_status = 1;
		return ;
	}
	data->last_status = command_exec(cmd->args, data);
	redir_restore(saved_stdin, saved_stdout);
}
