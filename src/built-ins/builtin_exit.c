/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:18:50 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/24 12:37:52 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	shell_exit(char	**args, t_env *shell_envp)
{
	(void)args;
	printf("Exiting ./minishell, freeing all allocated data...\n\n");
	free_shell_envp_list(&shell_envp);
	printf("Minishell: All data freed. Goodbye!!\n");
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
