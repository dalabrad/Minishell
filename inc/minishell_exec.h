/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:32:53 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/23 22:51:17 by dalabrad         ###   ########.fr       */
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

////////////////////////////////////////////////
//------ENVIRONMENT-----------------------------
////////////////////////////////////////////////

//	src/environment/envp_attribute_getters.c
char	*get_envp_name(char	*envp);
char	*get_envp_value(char *envp);

//	src/environment/shell_envp_list_utils.c
t_env	*new_shell_envp(char *envp, bool was_added);
t_env	*last_shell_envp(t_env *shell_envp);
void	add_shell_envp(t_env **shell_envp, t_env *new_shell_envp);
void	free_shell_envp_list(t_env **shell_envp);

//	src/environment/shell_envp_list_create.c
void	print_shell_envp_list(t_env *shell_envp);
int		shell_envp_list_create(char **envp, t_env **shell_envp);

////////////////////////////////////////////////
//------BUILT-INS-------------------------------
////////////////////////////////////////////////

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