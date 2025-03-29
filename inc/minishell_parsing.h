/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:21:52 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/29 13:24:31 by vlorenzo         ###   ########.fr       */
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

#define PROMPT "minishell>>"

// ENUM STRUCT
typedef enum t_TokenType
{
	RED_IN,
	RED_OUT,
	HEREDOC,
	APPEND_OUT,
	OPTION,
	COMMAND,
	SETTING,
	ARG,
	ERROR
}					t_TokenType;

typedef struct s_pipes // pipes
{
	char *str;
	int index;
	struct s_pipes *next;
}					t_pipes;

typedef struct s_tokens
{
	int				was_quoted;
	int				skip;
	char			*str;
	/* t_TokenType		type; */
	struct s_tokens	*next;
}					t_tokens;

char **ft_minisplit(const char *s, char c, int *n);
/* 
char **ft_free(char **split);
// char					**ft_minisplit(const char *s, char c);
size_t					wordcount(t_split *param, size_t limit);
bool					allocpy(t_split *param, t_parapos pos, size_t idpara);
size_t					ft_param_count(const char *s, char c);
bool					in_out_quotes(const char *s, size_t *i, char c);
void					ft_strlcpy_quote(char *dst, const char *src,
							size_t size);
*/

#endif
