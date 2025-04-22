/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:46:09 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/22 21:10:25 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

size_t	number_of_cmds(t_cmd *first_cmd)
{
	size_t	size;

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

	if (!cmd)
		return ;
	next = NULL;
	while (cmd)
	{
		if (cmd->args)
			free_array(cmd->args);
		if (cmd->file_in)
			free(cmd->file_in);
		if (cmd->file_out)
			free(cmd->file_out);
		next = cmd->next;
		free(cmd);
		cmd = next;
	}
}
