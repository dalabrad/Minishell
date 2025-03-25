/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:16:31 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/25 18:18:16 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	error_msg(t_err error_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error_code == MALLOC_ERROR)
		ft_putstr_fd("malloc: unable to allocate memory\n", 2);
	if (error_code == CD_ERROR)
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
	return (error_code);
}

void	error_msg_exit(t_err error_code)
{
	error_msg(error_code);
	exit (error_code);
}
