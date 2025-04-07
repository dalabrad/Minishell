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