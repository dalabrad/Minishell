/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:21:52 by dalabrad          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/22 12:05:06 by vlorenzo         ###   ########.fr       */
=======
/*   Updated: 2025/03/21 19:20:54 by dalabrad         ###   ########.fr       */
>>>>>>> 51d2cd090fb651d45ff029a7e0a1f6b242d0bba9
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

//////////////////////////////////
// HEADERS FROM INCLUDED LIBRARIES
//////////////////////////////////

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

//////////////////////////////////
// MINISHELL PROMTP
//////////////////////////////////

# define PROMPT "minishell>>"

//////////////////////////////////
// ARGUMENTS STRUCTURES
//////////////////////////////////

// ENUM STRUCT
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
// TOKENS
typedef struct s_tokens
{
	int					was_quoted;
	int					skip;
	char				*str;
	t_TokenType			type;
	struct s_tokens		*next;
}						t_tokens;
// ENVIRONMENT
typedef struct s_env
{
	bool				was_added;
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;
// COMMANDS
typedef struct s_commands
{
	t_env				*env;
	t_tokens			*token;
	int					i;
	struct s_commands	*next;
}						t_commands;

//////////////////////////////////
// FT_SPLIT
// MINI-SPLIT STRUCT
//////////////////////////////////

typedef struct s_split
{
	char				**split;
	const char			*s;
	char				c;
}						t_split;
// PARAMATER POSITION STRUCT
typedef struct s_param_pos
{
	size_t				start;
	size_t				end;
	bool				in_quotes;
	char				quote_char;
}						t_parapos;

char					**ft_free(char **split);
char					**ft_minisplit(const char *s, char c);
size_t					wordcount(t_split *param, size_t limit);
bool					allocpy(t_split *param, t_parapos pos, size_t idpara);
size_t					ft_param_count(const char *s, char c);
bool					quote_parse(const char *s, size_t *i, char separat);
void					ft_strlcpy_quote(char *dst, const char *src,
							size_t size);

#endif
