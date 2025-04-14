/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:39:42 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/10 19:21:02 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*shell_envp;
	int		status = 0;
	pid_t	pid;

	if (argc == 1)
	{
		printf("Error!!! Use:\n\t./minishell <command> <command_atribute> " \
			"<command_atribute>...\n");
		return (EXIT_FAILURE);
	}
	shell_envp = NULL;
	if (shell_envp_list_create(envp, &shell_envp))
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
		status += command_exec(argv, &shell_envp);
	else
	{
		waitpid(pid, NULL, 0);
		printf("\n========================================================\n\n");
	}
	free_shell_envp_list(&shell_envp);
	return (status);
}
