/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:18:50 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/24 11:20:39 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	shell_exit(char	**args, t_env *shell_envp)
{
	(void)args;
	printf("Exiting ./minishel...\n");
	free_shell_envp_list(&shell_envp);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
