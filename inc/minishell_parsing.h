/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:21:52 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/07 14:33:57 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

//////////////////////////////////
// HEADERS FROM INCLUDED LIBRARIES
//////////////////////////////////
# include "../libft/inc/libft.h"
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
# include <string.h>

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
