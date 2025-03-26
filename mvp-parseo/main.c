#include "../libft/inc/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROMPT "minishell>>"

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
}					t_TokenType;

typedef struct s_words // pipes
{
	char *str;
	int index;
	struct s_words *next;
}					t_words;

typedef struct s_tokens
{
	int				was_quoted;
	int				skip;
	char			*str;
	t_TokenType		type;
	struct s_tokens	*next;
}					t_tokens;

static t_words	*init_struct(t_words *args)
{
	args = malloc(sizeof(t_words));
	if (!args)
		return (NULL);
	args->index = 0;   // init struct
	args->str = NULL;  // init struct
	args->next = NULL; // init struct
	return (args);
}

static t_words	*clean_struct(t_words *args)
{
	t_words	*temp;

	temp = NULL;
	while (args->next) // LIBERAMOS TODO
	{
		temp = args;
		args = args->next;
		free(temp);
		temp = NULL;
	}
	return (temp);
}

void	ft_lstadd_front2(t_words **lst, t_words *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}

static size_t	count_splitted(const char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
		else if (s[i] == c)
			i++;
	}
	return (count);
}

static size_t	splitted_len(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

char **free_array(char **array)
{
	int	limit;

	limit = 0;
	while (array[limit] != 0)
	{
		free(array[limit]);
		array[limit] = NULL;
		limit++;
	}
	free(array);
	array = NULL;
	return (0);
}

static size_t	skip_separat(const char *s, char c, size_t pos)
{
	while (s[pos] == c && s[pos] != 0)
		pos++;
	return (pos);
}

static char	**split2array(const char *s, char c, char **array, size_t w_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < w_count)
	{
		while (s[j] != '\0' && s[j] == c)
			j++;
		// if balanceo de comillas NO OK --> readline
		// si OK, entonces guardar en array
		array[i] = ft_substr(s, j, splitted_len(&s[j], c));
		if (array[i] == NULL)
		{
			array = free_array(array);
			return (NULL);
		}
		j += splitted_len(&s[j], c);
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_minisplit(const char *s, char c, int *i_words)
{
	char	**array;

	if (s == NULL)
		return (NULL);
	*i_words = count_splitted(s, c); // cuenta pipes
	array = (char **)malloc(sizeof(char *) * (*i_words + 1));
	if (array == NULL)
		return (NULL);
	array = split2array(s, c, array, *i_words);
	return (array);
}

int	main(int ac, char **av) // luego usaremos readline + (void)ac,av
{
	int i;
	int i_words;
	int j_words;
	t_words *args;
	t_words *temp;
	char **res;
	char *str_exit = "exit";

	i = 0;
	i_words = 0;
	j_words = 0;

	args = init_struct(args);
	temp = args; // Guardamos HEAD
	while (1)
	{
		args = temp; // recuperamos HEAD
		args->str = readline(PROMPT);
		if (!strcmp(args->str, str_exit))
			break ;
		if (strchr(args->str, '|'))
			res = ft_minisplit(args->str, '|', &i_words); // i_words por REF
		else
		{
			res = malloc(sizeof(char **)); // Alloc
			*res = args->str;
		}

		j_words = i_words + 1; // i-words +1 devuelve tamaño de res** +NULL
		while (--i_words >= 0) // recogemos i_words
		{
			t_words *new_node = malloc(sizeof(t_words));
			if (!new_node)
				return (1);
			args->next = new_node;
			new_node->next = NULL;        // init NEXT
			new_node->str = res[i_words]; // metemos splitted en new_node
			new_node->index = i_words;    // metemos i_words en new_node
			if (new_node->next == NULL)
				break ;
			else
				ft_lstadd_front2(&new_node, new_node->next); // añadir encima
		}

		args = temp; // Recuperamos HEAD
		while (args && args->str)
		{
			printf("%s\n", args->str);
			printf("%d\n", args->index);
			if (args->next == NULL)
				break ;
			else
				args = args->next;
		}
		args = clean_struct(args);
		res = free_array(res);
	}
	args = temp; // Recuperamos HEAD
	args = clean_struct(args);
	free(args);
	return (0);
}

/*
echo "Lola que ase" >> out.txt | ls .l | wc -l
 */