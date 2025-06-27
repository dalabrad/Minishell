/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:32:53 by dalabrad          #+#    #+#             */
/*   Updated: 2025/06/27 20:08:05 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include "array_utils.h"
# include "libft.h"
# include "minishell_parsing.h"
# include "minishell_signals.h"
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

// Forward declarations
typedef struct s_tokens	t_tokens;
typedef struct s_cmd	t_cmd;

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
	DUP2_ERROR,
}						t_err;

typedef struct s_env
{
	bool				was_added;
	char				*name;
	char				*value;
	bool				visible;
	struct s_env		*next;
}						t_env;

typedef struct s_data	t_data;

typedef struct s_builtin
{
	char				*name;
	int					(*foo)(char **args, t_data *data);
}						t_builtin;

typedef struct s_cmd	t_cmd;

struct					s_cmd
{
	char				**args;
	char				*file_in;
	char				*file_out;
	// bool heredoc
	bool append_out; // esto es nuevo
	pid_t				pid;
	t_cmd				*next;
};

struct					s_data
{
	t_env				*shell_envp;
	t_builtin			g_builtin[8];
	int					pipes[2][2];
	t_cmd				*first_cmd;
	size_t				nbr_cmds;
	int					last_status;
};

////////////////////////////////////////////////
//------ERROR MESSAGES--------------------------
////////////////////////////////////////////////

//	src/error_messages/error_message.c
int						error_msg(t_err error_code);
int						error_msg_arg(t_err error_code, char *arg);
void					error_msg_exit(t_err error_code);

////////////////////////////////////////////////
//------ENVIRONMENT-----------------------------
////////////////////////////////////////////////

//	src/environment/envp_attribute_getters.c
char					*get_envp_name(char *envp);
char					*get_envp_value(char *envp);
char					*get_shell_envp_value(t_env *shell_envp,
							const char *name);

//	src/environment/shell_envp_list_utils_1.c
t_env					*new_shell_envp(char *envp, bool was_added);
t_env					*last_shell_envp(t_env *shell_envp);
char					*get_env_value_from_list(const char *name, t_env *env);
void 					add_shell_envp(t_env **env_list, t_env *new_node);

//	src/environment/shell_envp_list_utils_2.c
void					free_shell_envp_list(t_env **shell_envp);
void					delete_shell_envp_node(t_env **shell_envp,
							char *VAR_NAME);

//	src/environment/shell_envp_list_create.c
void					print_shell_envp_list(t_env *shell_envp);
int						shell_envp_list_create(char **envp, t_env **shell_envp);
char **shell_envp_to_array(t_env *env);
////////////////////////////////////////////////
//------MINISHELL_DATA--------------------------
////////////////////////////////////////////////

//	src/minishell_data/minishell_data.c
int						data_init(t_data *data, char **envp);
void					close_pipes(t_data *data);
void					free_data(t_data *data);

////////////////////////////////////////////////
//------BUILT-INS-------------------------------
////////////////////////////////////////////////

bool					is_builtin(char *cmd, t_data *data);
int 					builtin_export(char **args, t_data *data);
int						shell_unset(char **args, t_data *data);
int						shell_env(char **args, t_data *data);
int						shell_echo(char **args, t_data *data);
int						shell_cd(char **args, t_data *data);
int						shell_pwd(char **args, t_data *data);
int						shell_exit(char **args, t_data *data);

////////////////////////////////////////////////
//------COMMAND-EXECUTION-----------------------
////////////////////////////////////////////////

//	src/cmd_execution/find_path.c
char					*find_path(char **args, t_env **shell_envp);

//	src/cmd_execution/command_exec.c
int						command_exec(char **args, t_data *data);

// src/cmd_execution/one_command_pipeline.c
void					one_cmd_pipeline(t_data *data);

// src/cmd_execution/execute_pipeline.c
void					execute_pipeline(t_data *data);

// src/cmd_execution/cmd_type_utils.c
t_cmd					*new_cmd(void);
size_t					number_of_cmds(t_cmd *first_cmd);
void					free_cmd_list(t_cmd *cmd);
t_cmd					*last_cmd(t_cmd *cmd);

#endif