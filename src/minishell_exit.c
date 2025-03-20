/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:18:50 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/20 14:25:18 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	shell_exit(char	**args)
{
	(void)args;
	printf("Exiting ./minishel...\n");
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
