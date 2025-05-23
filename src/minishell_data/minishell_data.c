/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:25:36 by dalabrad          #+#    #+#             */
/*   Updated: 2025/05/19 10:54:41 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

/*FALTA DE INCLUIR: data->tokens_by_segment = NULL; */
int	data_init(t_data *data, char**envp)
{
	data->g_builtin[0] = (t_builtin){.name = "exit", .foo = shell_exit};
	data->g_builtin[1] = (t_builtin){.name = "env", .foo = shell_env};
	data->g_builtin[2] = (t_builtin){.name = "echo", .foo = shell_echo};
	data->g_builtin[3] = (t_builtin){.name = "pwd", .foo = shell_pwd};
	data->g_builtin[4] = (t_builtin){.name = "cd", .foo = shell_cd};
	data->g_builtin[5] = (t_builtin){.name = "export", .foo = shell_export};
	data->g_builtin[6] = (t_builtin){.name = "unset", .foo = shell_unset};
	data->g_builtin[7] = (t_builtin){.name = NULL, .foo = NULL};
	data->shell_envp = NULL;
	data->first_cmd = NULL;
	data->tokens_by_segment = NULL;
	data->line = NULL;
	data->pipe_segments = NULL;
	data->num_pipes = 0;
	if (shell_envp_list_create(envp, &(data->shell_envp)))
	{
		data->shell_envp = NULL;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	close_pipes(t_data *data)
{
	close(data->pipes[0][R_PIPE]);
	close(data->pipes[0][W_PIPE]);
	close(data->pipes[1][R_PIPE]);
	close(data->pipes[1][W_PIPE]);
}

void	free_data(t_data *data)
{
	free_shell_envp_list(&(data->shell_envp));
}
