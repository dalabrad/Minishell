/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:44:09 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/07/20 18:25:49 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"


int	is_invalid_redirection_sequence(t_tokens *token)
{
	if (!token || !token->next)
		return 0;
	if ((token->type == RED_IN || token->type == RED_OUT
		|| token->type == APPEND_OUT || token->type == HEREDOC)
		&& (token->next->type == RED_IN || token->next->type == RED_OUT
		|| token->next->type == APPEND_OUT || token->next->type == HEREDOC))
		return 1;
	return 0;
}

static void	handle_heredoc_child(const char *delim)
{
	char	buffer[4096];
	char	*delim_line;
	int		fd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	write(STDOUT_FILENO, "> ", 2);
	fd = open("/tmp/1", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		exit(1);

	delim_line = ft_strjoin(delim, "\n");
	if (!delim_line)
		exit(1);

	while (1)
	{
		ssize_t r = read(STDIN_FILENO, buffer, 4095);
		if (r <= 0)
			break;
		buffer[r] = '\0';
		if (ft_strcmp(buffer, delim_line) == 0)
			break;
		write(fd, buffer, r);
		write(STDOUT_FILENO, "> ", 2);
	}
	free(delim_line);
	close(fd);
	exit(0);
}

static int	process_heredoc_runtime(const char *delimiter)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (error_msg(FORK_ERROR), -1);
	else if (pid == 0)
		handle_heredoc_child(delimiter);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			return (-1);
	}
	return (0);
}

t_cmd	*tokens_to_cmd(t_tokens *tokens)
{
	t_cmd		*cmd;
	t_tokens	*tmp;
	size_t		args_count = 0;
	size_t		i = 0;

	cmd = new_cmd();
	if (!cmd)
		return (NULL);
	cmd->append_out = false;

	tmp = tokens;
	while (tmp)
	{
		if (is_invalid_redirection_sequence(tmp))
			return (syntax_error(tmp->next->str), free_cmd_list(cmd), NULL);
		if (tmp->type == COMMAND || tmp->type == ARG || tmp->type == OPTION
			|| tmp->type == PATH || tmp->type == SETTING)
			args_count++;
		tmp = tmp->next;
	}

	cmd->args = ft_calloc(args_count + 1, sizeof(char *));
	if (!cmd->args)
		return (free_cmd_list(cmd), NULL);

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == COMMAND || tmp->type == ARG || tmp->type == OPTION
			|| tmp->type == PATH || tmp->type == SETTING)
			cmd->args[i++] = ft_strdup(tmp->str);
		else if ((tmp->type == RED_OUT || tmp->type == APPEND_OUT) && tmp->next)
		{
			cmd->file_out = ft_strdup(tmp->next->str);
			cmd->append_out = (tmp->type == APPEND_OUT);
			tmp = tmp->next;
		}
		else if (tmp->type == RED_IN && tmp->next)
		{
			cmd->file_in = ft_strdup(tmp->next->str);
			tmp = tmp->next;
		}
		else if (tmp->type == HEREDOC && tmp->next)
		{
			if (process_heredoc_runtime(tmp->next->str) == -1)
				return (free_cmd_list(cmd), NULL);
			cmd->file_in = ft_strdup("/tmp/1");
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	// Validar que haya un comando real
	if (!cmd->args[0])
	{
		syntax_error("missing command after redirection");
		return (free_cmd_list(cmd), NULL);
	}

	return (cmd);
}
