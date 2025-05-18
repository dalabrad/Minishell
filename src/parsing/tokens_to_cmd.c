/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:44:09 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/05/18 16:44:21 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell_parsing.h"
# include "minishell_exec.h"

t_cmd	*tokens_to_cmd(t_tokens *tokens)
{
	t_cmd	*cmd;
	size_t	args_count;
	size_t	i;
	t_tokens	*tmp;

	cmd = new_cmd();
	if (!cmd)
		return (NULL);
	cmd->append_out = false;
	args_count = 0;
	tmp = tokens;
	while (tmp) 	// Cuenta argumentos válidos
	{
		if (tmp->type == COMMAND || tmp->type == ARG || tmp->type == OPTION || tmp->type == PATH)
			args_count++;
		tmp = tmp->next;
	}
	cmd->args = ft_calloc(args_count + 1, sizeof(char *));     // Reserva espacio para args
	if (!cmd->args)
		return (free_cmd_list(cmd), NULL);
	i = 0;
	tmp = tokens;
	while (tmp)
	{
        if (tmp->type == COMMAND || tmp->type == ARG || tmp->type == OPTION || tmp->type == PATH)
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
