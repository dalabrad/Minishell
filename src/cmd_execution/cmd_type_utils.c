/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:46:09 by dalabrad          #+#    #+#             */
/*   Updated: 2025/08/04 18:09:41 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->file_in = NULL;
	cmd->file_out = NULL;
	cmd->append_out = false;
	cmd->pid = 0;
	cmd->next = NULL;
	return (cmd);
}

size_t	number_of_cmds(t_cmd *first_cmd)
{
	size_t	size;

	if (!first_cmd)
		return (0);
	size = 0;
	while (first_cmd)
	{
		size++;
		first_cmd = first_cmd->next;
	}
	return (size);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*next;

	while (cmd)
	{
		next = cmd->next;
		if (cmd->args)
			free_array(cmd->args);
		if (cmd->file_in)
			free(cmd->file_in);
		if (cmd->file_out)
			free(cmd->file_out);
		free(cmd);
		cmd = next;
	}
}

t_cmd	*last_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd)
	{
		if (cmd->next == NULL)
			return (cmd);
		cmd = cmd->next;
	}
	return (NULL);
}
