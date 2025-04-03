/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:16:31 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/03 16:36:11 by dalabrad         ###   ########.fr       */
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
	if (error_code == CHDIR_ERROR)
		ft_putstr("chdir : unable to change process working directory\n");
	return (error_code);
}

int	error_msg_arg(t_err error_code, char *arg)
{
	if (!arg)
		return (0);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error_code == CD_NO_DIR || error_code == CD_NO_PERM)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		if (error_code == CD_NO_DIR)
			ft_putstr_fd(" : No such file or directory\n", STDERR_FILENO);
		else
			ft_putstr_fd(" : Permission denied\n", STDERR_FILENO);
	}
	return (error_code);
}

void	error_msg_exit(t_err error_code)
{
	error_msg(error_code);
	exit (error_code);
}
