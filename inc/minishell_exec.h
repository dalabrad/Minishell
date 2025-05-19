/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:32:53 by dalabrad          #+#    #+#             */
/*   Updated: 2025/05/19 11:02:07 by dalabrad         ###   ########.fr       */
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
# define R_PIPE 0
# define W_PIPE 1

typedef enum e_err
{
	MALLOC_ERROR = 1,
	CD_ERROR,
	CD_NO_DIR,
	CD_NO_PERM,
	CHDIR_ERROR,
	NO_PATH,
	CMD_NOT_FOUND,
	PIPE_ERROR,
	FORK_ERROR,
	DUP2_ERROR,     // esto es nuevo
}	t_err;

typedef struct s_env
{
	bool			was_added;
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data	t_data;

typedef struct s_builtin
{
	char	*name;
	int		(*foo)(char **args, t_data *data);
}	t_builtin;

typedef struct s_cmd	t_cmd;

struct s_cmd
{
	char	**args;
	char	*file_in;
	char	*file_out;
	bool	append_out;   // esto es nuevo
	pid_t	pid;
	t_cmd	*next;
};

typedef struct s_tokens t_tokens;
struct s_data
{
	t_env		*shell_envp;
	t_builtin	g_builtin[8];
	int			pipes[2][2];
	t_cmd		*first_cmd;
	size_t		nbr_cmds;
	t_tokens	**tokens_by_segment;
	char		*line;
	char 		**pipe_segments;
	size_t 		num_pipes;
};

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
void	close_pipes(t_data *data);
void	free_data(t_data *data);

////////////////////////////////////////////////
//------BUILT-INS-------------------------------
////////////////////////////////////////////////

//	src/built-ins/is_builtin.c
bool	is_builtin(char *cmd_name, t_data *data);

//	src/built-ins/builtin_cd.c
int		shell_cd(char **args, t_data *data);

//	src/built-ins/builtin_echo.c
int		shell_echo(char **args, t_data *data);

//	src/built-ins/builtin_env.c
int		shell_env(char **args, t_data *data);

//	src/built-ins/builtin_exit.c
int		shell_exit(char	**args, t_data *data);

//	src/built-ins/builtin_export.c
int		shell_export(char **args, t_data *data);

//	src/built-ins/builtin_pwd.c
int		shell_pwd(char **args, t_data *data);

//	src/built-ins/builtin_unset.c
int		shell_unset(char **args, t_data *data);

////////////////////////////////////////////////
//------COMMAND-EXECUTION-----------------------
////////////////////////////////////////////////

//	src/cmd_execution/find_path.c
char	*find_path(char **args, t_env **shell_envp);

//	src/cmd_execution/command_exec.c
int		command_exec(char **args, t_data *data);

// src/cmd_execution/one_command_pipeline.c
void	one_cmd_pipeline(t_data *data);

// src/cmd_execution/execute_pipeline.c
void	execute_pipeline(t_data *data);

// src/cmd_execution/cmd_type_utils.c
t_cmd	*new_cmd(void);
size_t	number_of_cmds(t_cmd *first_cmd);
void	free_cmd_list(t_cmd *cmd);
t_cmd	*last_cmd(t_cmd *cmd);

#endif