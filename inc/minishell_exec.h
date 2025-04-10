/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:32:53 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/10 16:38:44 by dalabrad         ###   ########.fr       */
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
	CD_ERROR,
	CD_NO_DIR,
	CD_NO_PERM,
	CHDIR_ERROR,
	NO_PATH,
	CMD_NOT_FOUND,
}	t_err;

typedef struct s_env
{
	bool			was_added;
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_builtin
{
	char	*builtin_name;
	int		(*foo)(char **args, t_env **shell_envp);
}	t_builtin;

////////////////////////////////////////////////
//------ERROR MESSAGES--------------------------
////////////////////////////////////////////////

//	src/error_messages/error_message.c
int		error_msg(t_err error_code);
int		error_msg_arg(t_err error_code, char *arg);
void	error_msg_exit(t_err error_code);

////////////////////////////////////////////////
//------ARRAY-UTILS-----------------------------
////////////////////////////////////////////////

//  src/array_utils/array_utils.c

void	free_array(char **array);
size_t	array_size(char **array);
void	print_array(char **array);

////////////////////////////////////////////////
//------ENVIRONMENT-----------------------------
////////////////////////////////////////////////

//	src/environment/envp_attribute_getters.c
char	*get_envp_name(char	*envp);
char	*get_envp_value(char *envp);
char	*get_shell_envp_value(t_env *shell_envp, const char *name);

//	src/environment/shell_envp_list_utils_1.c
t_env	*new_shell_envp(char *envp, bool was_added);
t_env	*last_shell_envp(t_env *shell_envp);
void	add_shell_envp(t_env **shell_envp, t_env *new_shell_envp);

//	src/environment/shell_envp_list_utils_2.c
void	free_shell_envp_list(t_env **shell_envp);
void	delete_shell_envp_node(t_env **shell_envp, char *VAR_NAME);

//	src/environment/shell_envp_list_create.c
void	print_shell_envp_list(t_env *shell_envp);
int		shell_envp_list_create(char **envp, t_env **shell_envp);

////////////////////////////////////////////////
//------BUILT-INS-------------------------------
////////////////////////////////////////////////

//	src/built-ins/builtin_cd.c
int		shell_cd(char **args, t_env **shell_envp);

//	src/built-ins/builtin_echo.c
int		shell_echo(char **args, t_env **shell_envp);

//	src/built-ins/builtin_env.c
int		shell_env(char **args, t_env **shell_envp);

//	src/built-ins/builtin_exit.c
int		shell_exit(char	**args, t_env **shell_envp);

//	src/built-ins/builtin_export.c
int		shell_export(char **args, t_env **shell_envp);

//	src/built-ins/builtin_pwd.c
int		shell_pwd(char **args, t_env **shell_envp);

//	src/built-ins/builtin_unset.c
int		shell_unset(char **args, t_env **shell_envp);

//------------------------------------------

//	src/command_exec.c
int		command_exec(char **args, t_env **shell_envp);

#endif