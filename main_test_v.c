/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_van.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:06:21 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/03/19 18:54:55 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "minishell_exec.h" */
#include "minishell_parsing.h"

#include "mvp.h"

static t_pipes	*init_struct(t_pipes *args)
{
	args = malloc(sizeof(t_pipes));
	if (!args)
		return (NULL);
	args->index = 0;   // init struct
	args->str = NULL;  // init struct
	args->next = NULL; // init struct
	return (args);
}

/* static t_tokens init_token
{
	0, 0, NULL, NULL
} // Inicializamos struct t_tokens */
bool	quote_parse(const char *s, size_t *i, char separat)
{
	bool	in_quotes;
	char	quote_char;

	in_quotes = false;
	quote_char = '\0';
	while (s[*i] != 0 && (s[*i] != separat || in_quotes))
	{
		if ((s[*i] == 34 || s[*i] == 39) && !in_quotes)
		{
			in_quotes = true;
			quote_char = s[*i];
		}
		else if (s[*i] == quote_char && in_quotes)
			in_quotes = false;
		(*i)++;
	}
	return (in_quotes);
}

t_TokenType	clasify_token(const char *str)
{
	enum t_TokenType	type;
	int i;

	i = 0;

/* 	// COMMAND
	if(i == 0)
	{
		
	} */
	
	// REDIRECTIONS
	if (strcmp(&str[i], "<"))
	{
		if(i == 0)
		{
			if(strcmp(&str[i + 1], "<") && str[i + 2] != '<')
				return (printf("HEREDOC %s\n", str));
			else if(strcmp(&str[i + 1], "<") && str[i + 2] == ' ')
				return (RED_IN);
		}
		else if(i != 0 && str[i - 1] != ' ')
				return (ERROR);
		else if(i != 0 && str[i + 1] == '<' && str[i + 2] != '<')
			return (HEREDOC);
		else if(i != 0  && strcmp(&str[i + 1], "<") && str[i + 2] == ' ')
			return (RED_IN);
	}
	if (strcmp(&str[i], ">"))
	{
		if(i == 0)
		{
			if(strcmp(&str[i + 1], ">") && str[i + 2] != '>')
				return (APPEND_OUT);
			else if(strcmp(&str[i + 1], ">") && str[i + 2] == ' ')
				return (RED_OUT);
		}
		else if(i != 0 && str[i - 1] != ' ')
				return (ERROR);
		else if(i != 0 && str[i + 1] == '>' && str[i + 2] != '>')
			return (APPEND_OUT);
		else if(i != 0  && strcmp(&str[i + 1], ">") && str[i + 2] == ' ')
			return (RED_OUT);
	}
	// OPTIONS
	if (strcmp(&str[i], "-") && (str[i + 1]))
		return (OPTION);
	
	return (type);
}

static t_pipes	*clean_struct(t_pipes *args)
{
	t_pipes	*temp;

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

void	ft_lstadd_front2(t_pipes **lst, t_pipes *new)
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

char	**free_array(char **array)
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

t_tokens	*check_args(t_pipes *args)
{
	t_pipes			*temp;
	t_tokens		*token;
	int				i;
	int				j;
	int				i_words;
	char			**words;
	
	i = 0;
	j = 0;
	i_words = 0;
	token = malloc(sizeof(t_tokens));
	*token = (t_tokens){0, 0, NULL, NULL}; // Inicializamos struct t_tokens
	temp = args;
	while (temp && temp->next)
	{
		words = ft_minisplit(args[i].str, ' ', &i_words);
		while (words[j++])
		{
			write(1, "---WHILE DE WORDS---", 21);
			token->str = words[j];
			clasify_token(token->str);
			token = token->next;
		}
	}
	return (token);
}

static const char	*skip_space(const char *s)
{
	while (*s == ' ' && *s != 0)
		s++;
	return (s);
}

static int	is_open(const char *s)
{
	int		i;
	bool	is_single_quote;
	bool	is_double_quote;

	is_single_quote = false; // 0
	is_double_quote = false; // 0
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' && s[i - 1] != '\\' && !is_double_quote)
			is_single_quote = !is_single_quote;
		else if (s[i] == '\"' && s[i - 1] != '\\' && !is_single_quote)
			is_double_quote = !is_double_quote; // invierte el valor de entrada
		i++;
	}
	return (is_single_quote || is_double_quote);
}

static char	**split2array(const char *s, char c, char **array, size_t w_count)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*chop;

	i = 0;
	j = 0;
	k = 0;
	while (i < w_count)
	{
		while (s[j] != '\0' && s[j] != c)
			j++;
		chop = ft_substr(s, k, (j - k));
		if ( s[j] != '\0' && s[j + 1] != '\0')
			j++;           // siguiente a PIPE
		if (is_open(chop)) // si cualquier valor != 0
		{
			write(1, "Syntax error\n", 14);
			return (NULL);
		}
		array[i] = ft_substr(s, k, splitted_len(&s[k], c));
		if (array[i] == NULL)
		{
			array = free_array(array);
			return (NULL);
		}
		k = j;
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_minisplit(const char *s, char c, int *n)
{
	char	**array;

	if (s == NULL)
		return (NULL);
	s = skip_space(s);
	*n = count_splitted(s, c); // cuenta pipes
	array = (char **)malloc(sizeof(char *) * (*n + 1));
	if (array == NULL)
		return (NULL);
	array = split2array(s, c, array, *n);
	return (array);
}

int	main(int argc, char **argv, char **envp)
{
	int i;
	int		i_pipes;
	int		j_pipes;
	int		fd;
	t_pipes	*args;
	t_pipes	*temp;
	t_pipes	*temp2;
	char	**res;
	char	*str_exit;
	t_pipes	*new_node;
	(void)argv;
	(void)envp;

	new_node = init_struct(new_node);
	fd = 0;
	str_exit = "exit";
	i = 0;
	i_pipes = 0;
	j_pipes = 0;
	if (argc != 1)
		return (printf("Too many arguments or readline failure.\n"), 0);
	args = init_struct(args);
	temp = args; // Guardamos HEAD
	temp2 = new_node;
	while (1)
	{
		fd = dup(STDIN_FILENO);
		args = temp; // recuperamos HEAD
		args->str = readline(PROMPT);
		if (!strcmp(args->str, str_exit)) // Salimos con "exit"
			break ;
		if (strchr(args->str, '|'))
			res = ft_minisplit(args->str, '|', &i_pipes); // i_pipes por REF
		else
		{
			i_pipes = 0;
			res = malloc(sizeof(char **)); // Alloc
			*res = args->str;
		}
		j_pipes = i_pipes + 1;        // i-words+1 devuelve tamaño de res**+NULL

		while (res && --j_pipes >= 0) // recogemos j_pipes
		{
			new_node = malloc(sizeof(t_pipes));
			if (!new_node)
				return (1);
			new_node->str = res[i];
			new_node->index = i++;
			new_node->next = NULL;
			printf("----> INDEX %d\n", new_node->index);
			printf("----> NODE[I] %s\n", new_node->str);
			if (new_node->str == NULL)
				break ;
			else
				ft_lstadd_front2(&new_node, new_node->next); // añadir encima
		}
		new_node = temp2;
		printf("ARGS TRAS 1ER SPLIT %s\n", new_node->str);
		check_args(args);
	}
	args = temp; // Recuperamos HEAD
	new_node = temp2;
	args = clean_struct(args);
	free(args);
	return (0);
}

/*
> PARA PROBAR:
>
> make testv
> ./minishell + ENTER
> minishell>> echo "Lola que ase" >> out.txt | ls .l | wc -l
*/

/* // MAIN ANTERIOR QUE NO SIRVE 
int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		fd;
	char	**prompts;
	int		i;

	(void)argv;
	(void)envp;
	line = NULL;
	prompts = NULL;
	if (argc == 1)
	{
		while (1)
		{
			fd = dup(STDIN_FILENO);
			line = readline(PROMPT);
			if (!line)
				break ;
			prompts = ft_minisplit(line, ' ');
			if (prompts)
			{
				i = 0;
				while (prompts[i])
				{
					printf("Prompt[%d]: %s\n", i, prompts[i]);
					i++;
				}
				prompts = ft_free(prompts);
			}
			printf("%s\n", line);
			free(line);
			close(fd);
		}
	}
	else
	{
		printf("Too many arguments or readline failure.\n");
	}
	return (0);
} */
