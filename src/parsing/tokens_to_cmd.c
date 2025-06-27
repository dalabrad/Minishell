/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:44:09 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/06/27 19:53:07 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int is_invalid_redirection_sequence(t_token *token)
{
    if (!token || !token->next)
        return 0;
    if ((token->type == RED_IN || token->type == RED_OUT || token->type == APPEND_OUT || token->type == HEREDOC) &&
        (token->next->type == RED_IN || token->next->type == RED_OUT || token->next->type == APPEND_OUT || token->next->type == HEREDOC))
        return 1;
    return 0;
}

t_cmd *tokens_to_cmd(t_tokens *tokens)
{
    t_cmd       *cmd;
    size_t      args_count;
    size_t      i;
    t_tokens    *tmp;

    cmd = new_cmd();
    if (!cmd)
        return (NULL);
    cmd->append_out = false;
    args_count = 0;
    tmp = tokens;
    while (tmp) // Cuenta argumentos válidos
    {
        if (is_invalid_redirection_sequence(tmp))
            return syntax_error(tmp->next->str);

        if (tmp->type == COMMAND || tmp->type == ARG || tmp->type == OPTION
            || tmp->type == PATH || tmp->type == SETTING)
            args_count++;
        tmp = tmp->next;
    }
    cmd->args = ft_calloc(args_count + 1, sizeof(char *));
    if (!cmd->args)
        return (free_cmd_list(cmd), NULL);
    i = 0;
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
        else if ((tmp->type == RED_IN) && tmp->next)
        {
            cmd->file_in = ft_strdup(tmp->next->str);
            tmp = tmp->next;
        }
        tmp = tmp->next;
    }
    return (cmd);
}
