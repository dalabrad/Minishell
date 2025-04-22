/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:39:42 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/22 20:59:42 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static int	create_cmds(t_data *data)
{
	t_cmd	*ls = (t_cmd *)malloc(sizeof(t_cmd));
	t_cmd	*grep = (t_cmd *)malloc(sizeof(t_cmd));
	t_cmd	*wc= (t_cmd *)malloc(sizeof(t_cmd));

	if (!ls || !grep || !wc)
	{
		fprintf(stderr, "malloc error!\n");
		return (EXIT_FAILURE);
	}
	data->first_cmd = ls;
	ls->next = grep;
	grep->next = wc;
	wc->next = NULL;
	ls->args = ft_split("ls -la", ' ');
	if (!ls->args)
	{
		fprintf(stderr, "malloc error!\n");
		return (EXIT_FAILURE);
	}
	grep->args = ft_split("grep m", ' ');
	if (!grep->args)
	{
		fprintf(stderr, "malloc error!\n");
		return (EXIT_FAILURE);
	}
	wc->args = ft_split("wc -l", ' ');
	if (!wc->args)
	{
		fprintf(stderr, "malloc error!\n");
		return (EXIT_FAILURE);
	}
	ls->file_in = NULL;
	ls->file_out = NULL;
	grep->file_in = NULL;
	grep->file_out = NULL;
	wc->file_in = NULL;
	wc->file_out = NULL;
	data->nbr_cmds = number_of_cmds(data->first_cmd);
	printf ("Number of commands = %lu\n", data->nbr_cmds);
	return (EXIT_SUCCESS);
}

/* static int	create_cmds(t_data *data)
{
	t_cmd	*cmd = (t_cmd *)malloc(sizeof(t_cmd));

	if (!cmd)
	{
		fprintf(stderr, "malloc error!\n");
		return (EXIT_FAILURE);
	}
	data->first_cmd = cmd;
	cmd->next = NULL;
	cmd->args = ft_split("env", ' ');
	if (!cmd->args)
	{
		fprintf(stderr, "malloc error!\n");
		return (EXIT_FAILURE);
	}
	cmd->file_in = NULL;
	cmd->file_out = NULL;
	data->nbr_cmds = number_of_cmds(data->first_cmd);
	printf ("Number of commands = %lu\n", data->nbr_cmds);
	return (EXIT_SUCCESS);
} */

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1)
	{
		printf("Error!!! Use:\n\t./minishell\n");
		return (EXIT_FAILURE);
	}
	(void)argv;
	if (data_init(&data, envp))
		return (EXIT_FAILURE);
	if (create_cmds(&data))
		return (EXIT_FAILURE);
	execute_pipeline(&data);
	free_cmd_list(data.first_cmd);
	free_data(&data);
	return (EXIT_SUCCESS);
}