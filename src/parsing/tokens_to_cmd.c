/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:44:09 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/06/29 12:31:04 by vlorenzo         ###   ########.fr       */
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
		{
			syntax_error(tmp->next->str);
			return (free_cmd_list(cmd), NULL);
		}
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
		tmp = tmp->next;
	}
	return (cmd);
}
