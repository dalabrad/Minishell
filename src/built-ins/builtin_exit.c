/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:18:50 by dalabrad          #+#    #+#             */
/*   Updated: 2025/05/19 10:57:35 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	shell_exit(char	**args, t_data *data)
{
	(void)args;
	if (data->nbr_cmds == 1)
		printf("exit\n");
	free_data(data);
	free_cmd_list(data->first_cmd);
	cleanup(data->line, data->pipe_segments, data->tokens_by_segment,
			data->num_pipes);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
