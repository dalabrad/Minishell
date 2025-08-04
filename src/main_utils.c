/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 00:29:51 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/08/04 21:35:15 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell_exec.h"
#include "minishell_parsing.h"
#include <unistd.h>
#include <stdio.h>

void	restore_stdio(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}
