/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:32:53 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/15 18:29:11 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include "libft.h"
# include "minishell_parsing.h"
# include "array_utils.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

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
	char	*name;
	int		(*foo)(char **args, t_env **shell_envp);
}	t_builtin;

typedef struct s_data
{
	t_env		*shell_envp;
	//t_tokens	*tokens_by_segment;
	t_builtin	g_builtin[8];
}	t_data;

////////////////////////////////////////////////
//------ERROR MESSAGES--------------------------
////////////////////////////////////////////////

//	src/error_messages/error_message.c
int		error_msg(t_err error_code);
int		error_msg_arg(t_err error_code, char *arg);
void	error_msg_exit(t_err error_code);

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
//------MINISHELL_DATA--------------------------
////////////////////////////////////////////////

//	src/minishell_data/minishell_data.c
int		data_init(t_data *data, char**envp);
void	free_data(t_data *data);

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

////////////////////////////////////////////////
//------COMMAND-EXEC----------------------------
////////////////////////////////////////////////

//	src/cmd_execution/command_exec.c
int		command_exec(char **args, t_data data);

#endif