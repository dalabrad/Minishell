/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:39:42 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/15 18:21:49 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	pid_t	pid;

	if (argc == 1)
	{
		printf("Error!!! Use:\n\t./minishell <command> <command_atribute> " \
			"<command_atribute>...\n");
		return (EXIT_FAILURE);
	}
	if (data_init(&data, envp))
		return (EXIT_FAILURE);
	argv++;
	printf("\n=======================================================\n\n");
	pid = fork();
	if (pid == -1)
	{
		printf("minishel: could not fork process\n");
		return (EXIT_FAILURE);
	}
	else if (!pid)
		command_exec(argv, data);
	else
	{
		waitpid(pid, NULL, 0);
		printf("\n========================================================\n\n");
	}
	free_data(&data);
	return (EXIT_SUCCESS);
}