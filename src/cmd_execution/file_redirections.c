/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:44:44 by dalabrad          #+#    #+#             */
/*   Updated: 2025/07/28 19:16:50 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

void	file_in_redir(t_cmd *cmd)
{
	int	fd_in;

	fd_in = open(cmd->file_in, O_RDONLY);
	if (fd_in < 0)
		exit(error_msg_arg(NO_PATH, cmd->file_in));
	if (dup2(fd_in, STDIN_FILENO) < 0)
		exit(error_msg(DUP_ERROR));
	close(fd_in);
}

void	file_out_redir(t_cmd *cmd)
{
	int	fd_out;

	if (cmd->append_out)
		fd_out = open(cmd->file_out, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd_out = open(cmd->file_out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out < 0)
		exit(error_msg_arg(NO_PATH, cmd->file_out));
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		exit(error_msg(DUP_ERROR));
	close(fd_out);
}
