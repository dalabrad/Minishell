/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:25:36 by dalabrad          #+#    #+#             */
/*   Updated: 2025/06/29 12:47:40 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	data_init(t_data *data, char **envp)
{
	data->g_builtin[0] = (t_builtin){.name = "exit", .foo = shell_exit};
	data->g_builtin[1] = (t_builtin){.name = "env", .foo = shell_env};
	data->g_builtin[2] = (t_builtin){.name = "echo", .foo = shell_echo};
	data->g_builtin[3] = (t_builtin){.name = "pwd", .foo = shell_pwd};
	data->g_builtin[4] = (t_builtin){.name = "cd", .foo = shell_cd};
	data->g_builtin[5] = (t_builtin){.name = "export", .foo = builtin_export};
	data->g_builtin[6] = (t_builtin){.name = "unset", .foo = shell_unset};
	data->g_builtin[7] = (t_builtin){.name = NULL, .foo = NULL};
	data->shell_envp = NULL;
	data->first_cmd = NULL;
	data->tokens_by_segment = NULL;
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
	size_t	i;

	if (!data)
		return;

	//Libera comandos
	if (data->first_cmd)
		free_cmd_list(data->first_cmd);

	//Libera entorno shell
	if (data->shell_envp)
		free_shell_envp_list(&(data->shell_envp));

	//Libera tokens_by_segment
	if (data->tokens_by_segment)
	{
		i = 0;
		while (i < data->nbr_cmds)
		{
			if (data->tokens_by_segment[i])
				free_tokens_list(data->tokens_by_segment[i]);
			i++;
		}
		free(data->tokens_by_segment);
	}

	//Limpia historial readline
	rl_clear_history();

	//NO libera data, ya que no fue mallocado.
}

