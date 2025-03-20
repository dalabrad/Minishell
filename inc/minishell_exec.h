/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:32:53 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/20 12:25:13 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include "../libft/inc/libft.h"
# include "minishell_parsing.h"
# include <stdio.h>

typedef struct s_builtin
{
	char	*builtin_name;
	int		(*foo)(char **args);
}	t_builtin;

//------BUILT-INS---------------------------

//	src/minishell_cd.c
int		shell_cd(char **args);

//	src/minishell_echo.c
int		shell_echo(char **args);

//	src/minishell_env.c
int		shell_env(char **args);

//	src/minishell_exit.c
int		shell_exit(char	**args);

//	src/minishell_export.c
int		shell_export(char **args);

//	src/minishell_pwd.c
int		shell_pwd(char **args);

//------------------------------------------

//	src/minishell_exec.c
void	shell_exec(char **args);

#endif