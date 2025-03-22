/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:32:53 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/21 20:08:04 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include "libft.h"
# include "minishell_parsing.h"
# include <stdio.h>

# define MAX_ENV 100

typedef enum e_err
{
	MALLOC_ERROR = 1,
	PIPE_ERROR,
}	t_err;

typedef struct s_builtin
{
	char	*builtin_name;
	int		(*foo)(char **args);
}	t_builtin;

//------BUILT-INS---------------------------

//	src/built-ins/builtin_cd.c
int		shell_cd(char **args);

//	src/built-ins/builtin_echo.c
int		shell_echo(char **args);

//	src/built-ins/builtin_env.c
int		shell_env(char **args);

//	src/built-ins/builtin_exit.c
int		shell_exit(char	**args);

//	src/built-ins/builtin_export.c
int		shell_export(char **args);

//	src/built-ins/builtin_pwd.c
int		shell_pwd(char **args);

//------------------------------------------

//	src/command_exec.c
void	command_exec(char **args);

#endif