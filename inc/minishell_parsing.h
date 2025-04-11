/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:21:52 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/11 14:07:40 by vlorenzo         ###   ########.fr       */
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
//-----MINISHELL PROMTP----------
//////////////////////////////////

# define PROMPT "minishell>>"

//////////////////////////////////
//-----STRUCTURES----------------
//////////////////////////////////

// ENUM TOKENS STRUCT
typedef enum t_TokenType {
	RED_IN,
	RED_OUT,
	HEREDOC,
	APPEND_OUT,
	OPTION,
	COMMAND,
	SETTING,
	ARG,
	ERROR
}						t_TokenType;
// PIPES
typedef struct s_pipes // pipes
{
	char *str;
	size_t index;
	struct s_pipes *next;
}						t_pipes;
// TOKENS
typedef struct s_tokens
{
	int					was_quoted;
	int					skip;
	char				*str;
	t_TokenType			type;
	struct s_tokens		*next;
}						t_tokens;

// COMMANDS
typedef struct s_commands
{
	/* t_env				*env; */
	t_tokens			*token;
	int					i;
	struct s_commands	*next;
}						t_commands;

// MINI-SPLIT STRUCT
typedef struct s_split
{
	char				**split;
	const char			*s;
	char				c;
}						t_split;

//////////////////////////////////
//-----FUNCTIONS-----------------
//////////////////////////////////

// UTILS INIT CLEAN STRUCTS
void 					**free_array2(char **array);
t_pipes 				*init_struct(t_pipes *args);
t_pipes					*clean_struct(t_pipes *args);
void 					free_tokens_list(t_tokens *head);

// FT-MINI-SPLIT
size_t					splitted_len(const char *s, char c);
char					**split2array(const char *s, char c, char **array,
							size_t w_count);
char					**ft_minisplit(const char *s, char c, size_t *n);
size_t					count_splitted(const char *s, char c);

// UTILS PARSING
void					print_tokens(t_tokens *list);
int ft_lstadd_front2(t_pipes **lst, t_pipes *new);
const char				*skip_space(const char *s);
size_t					is_open(const char *s);

// FT_CLASIFY TOKENS
t_TokenType				clasify_token(const char *str);
void 					set_command_type(t_tokens *tokens);
const 					char *token_type_str(t_TokenType type);
char *poly_substr(const char *s, size_t *i, int *was_quoted);
t_tokens				*check_args_fixed(const char *input, size_t *i_words);

#endif
