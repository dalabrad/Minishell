/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:21:52 by dalabrad          #+#    #+#             */
/*   Updated: 2025/05/10 16:27:27 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

//////////////////////////////////
// HEADERS FROM INCLUDED LIBRARIES
//////////////////////////////////

# include "libft.h"
# include "minishell_exec.h"
# include "array_utils.h"
# include <stddef.h>
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
#include <string.h>

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
	PATH,
	ARG,
	ERROR
}						t_TokenType;
// PIPES
typedef struct s_pipes // pipes
{
	char *str;
	size_t index;
	struct s_pipes *next;
}	t_pipes;

// TOKENS
typedef struct s_tokens	t_tokens;

struct s_tokens
{
	int					was_quoted;
	int					skip;
	char				*str;
	t_TokenType			type;
	t_tokens			*next;
};

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

// UTILS INIT & HANDLE
int						handle_token_alloc_fail(char **segments, char *line);
t_pipes 				*init_struct(t_pipes *args);
int						init_pipe_segments(char *line, char ***segments, size_t *n);
t_tokens 				**init_tokens_by_segment(size_t count);

// UTILS CLEAN STRUCTS

t_pipes					*clean_struct(t_pipes *args);
void 					free_tokens_list(t_tokens *head);
int						is_exit_command(char *line);
void 					cleanup(char *line, char **segments, t_tokens **tokens, size_t n);

// FT-MINI-SPLIT
size_t					splitted_len(const char *s, char c);
char					**split2array(const char *s, char c, char **array,
							size_t w_count);
char					**ft_minisplit(const char *s, char c, size_t *n);
size_t					count_splitted(const char *s, char c);

// UTILS PARSING
int 					is_path(const char *str);
int 					is_path(const char *str);
void					print_tokens(t_tokens *list);
int 					ft_lstadd_front2(t_pipes **lst, t_pipes *new);
int 					ft_lstadd_front2(t_pipes **lst, t_pipes *new);
const char				*skip_space(const char *s);
size_t					is_open(const char *s);

// FT_CLASIFY TOKENS
t_TokenType				clasify_token(const char *str);
void 					set_command_type(t_tokens *tokens);
const 					char *token_type_str(t_TokenType type);
char 					*poly_substr(const char *s, size_t *i, int *was_quoted);
t_tokens				*check_args_fixed(const char *input, size_t *i_words);

// PROCESS BY SEGMENT OR PIPE
void process_single_segment(char *segment, t_tokens **token_ptr, size_t index);
void process_segments(char **segments, t_tokens **tokens, size_t n);

// EXPAND & FOR EXEC
char	**tokens_to_args(t_tokens *tokens);
int		handle_redirections(t_tokens *tokens);
char 	*expand_variables(char *str);

#endif