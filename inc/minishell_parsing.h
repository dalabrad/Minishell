/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:21:52 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/20 17:56:21 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include "libft.h"
# include "minishell_exec.h"
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

# define PROMPT "minishell>>"

typedef enum t_TokenType
{
	SETTING,
	COMMAND,
	OPTION,
	PIPE,
	ARG,
	RED_IN,
	RED_OUT,
	HEREDOC,
	APPEND_OUT,
	ERRO
}						t_TokenType;

typedef struct s_tokens
{
	int					was_quoted;
	int					skip;
	char				*str;
	t_TokenType			type;
	struct s_tokens		*next;
}						t_tokens;

typedef struct s_env
{
	int					was_added;
	char				*name;
	char				*value;
	char				*str;
	struct s_env		*next;
}						t_env;

typedef struct s_commands
{
	t_env				*env;
	t_tokens			*token;
	int					index;
	struct s_commands	*next;
}						t_commands;

#endif
