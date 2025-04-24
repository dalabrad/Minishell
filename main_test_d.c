/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:39:42 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/24 12:18:13 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static int	create_cmds(t_data *data, int argc, char **argv)
{
	int	i = 0;

	while (i < argc)
	{
		t_cmd	*cmd = (t_cmd *)malloc(sizeof(t_cmd));

		if (!cmd)
		{
			//free_cmd_list(data->first_cmd);
			error_msg(MALLOC_ERROR);
			return (EXIT_FAILURE);
		}
		cmd->args = ft_split(argv[i], ' ');
		if (!cmd->args)
		{
			//free_cmd_list(data->first_cmd);
			error_msg(MALLOC_ERROR);
			return (EXIT_FAILURE);
		}
		cmd->file_in = NULL;
		cmd->file_out = NULL;
		cmd->next = NULL;
		if (i == 0)
			data->first_cmd = cmd;
		else
		{
			t_cmd *last = last_cmd(data->first_cmd);

			last->next = cmd;
		}
		i++;
	}
	data->nbr_cmds = number_of_cmds(data->first_cmd);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc == 1)
	{
		printf("Error!!! Use:\n\t./minishell <cmd_1> <cmd_2> ... <cmd_n>\n");
		return (EXIT_FAILURE);
	}
	if (data_init(&data, envp))
		return (EXIT_FAILURE);
	if (create_cmds(&data, argc - 1, argv + 1))
		return (EXIT_FAILURE);
	execute_pipeline(&data);
	free_cmd_list(data.first_cmd);
	free_data(&data);
	return (EXIT_SUCCESS);
}