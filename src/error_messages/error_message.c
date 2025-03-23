/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:16:31 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/23 23:29:13 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	error_msg(t_err error_code)
{
	ft_putstr_fd("Minishell: ", 2);
	if (error_code == MALLOC_ERROR)
		ft_putstr_fd("Malloc Error: unable to allocate memory.\n", 2);
	return (error_code);
}

void	error_msg_exit(t_err error_code)
{
	error_msg(error_code);
	exit (error_code);
}
