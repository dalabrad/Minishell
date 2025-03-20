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

#include "minishell_parsing.h"
#include "minishell_exec.h"

// MINI-SPLIT STRUCT
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
}						t_param_pos;

// FREE FUNCTION
char	**ft_free(char **split)
{
	int	limit;

	limit = 0;
	while (split[limit] != 0)
	{
		free(split[limit]);
		split[limit] = NULL;
		limit++;
	}
	free(split);
	split = NULL;
	return (0);
}

// PARSING QUOTES FUNCTION
bool	ft_quote_parsing(const char *s, size_t *index, char separator)
{
	bool	in_quotes;
	char	quote_char;

	in_quotes = false;
	quote_char = '\0';
	while (s[*index] != 0 && (s[*index] != separator || in_quotes))
	{
		if ((s[*index] == 34 || s[*index] == 39) && !in_quotes)
		{
			in_quotes = true;
			quote_char = s[*index];
		}
		else if (s[*index] == quote_char && in_quotes)
			in_quotes = false;
		(*index)++;
	}
	return (in_quotes);
}

// COUNT PARAMETERS FUNCTION
size_t	ft_param_count(char const *s, char c)
{
	size_t	init;
	size_t	count;

	init = 0;
	count = 0;
	while (s[init] != 0)
	{
		while (s[init] == c && s[init] != 0)
			init++;
		if (s[init] != 0)
		{
			count++;
			ft_quote_parsing(s, &init, c);
		}
	}
	return (count);
}

// STRING COPY BETWEEN SEPARATOR
void	ft_strlcpy_quote(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

// IGNORE SEPARATOR
static size_t	skip_separator(const char *s, char c, size_t pos)
{
	while (s[pos] == c && s[pos] != 0)
		pos++;
	return (pos);
}

static t_param_pos	param_end(const char *s, char c, size_t start)
{
	t_param_pos	pos;

	pos.start = start;
	pos.end = start;
	pos.in_quotes = false;
	pos.quote_char = '\0';
	while (s[pos.end] != 0 && (s[pos.end] != c || pos.in_quotes))
	{
		if ((s[pos.end] == 34 || s[pos.end] == 39) && !pos.in_quotes)
		{
			pos.in_quotes = true;
			pos.quote_char = s[pos.end];
		}
		else if (s[pos.end] == pos.quote_char && pos.in_quotes)
			pos.in_quotes = false;
		pos.end++;
	}
	return (pos);
}

// MEMO ALLOC FOR PARAMETER
bool	alloc_copy(t_split *params, t_param_pos pos, size_t id_param)
{
	params->split[id_param] = malloc(sizeof(char) * (pos.end - pos.start + 1));
	if (!params->split[id_param])
		return (false);
	ft_strlcpy_quote(params->split[id_param], params->s + pos.start, pos.end
		- pos.start + 1);
	return (true);
}

// SPLIT WORD COUNT FUNCTION
size_t	wordcount(t_split *params, size_t limit)
{
	t_param_pos	pos;

	pos.start = 0;
	pos.end = 0;
	pos.in_quotes = false;
	pos.quote_char = '\0';
	while (params->split[limit] == NULL)
	{
		pos.start = skip_separator(params->s, params->c, pos.end);
		pos = param_end(params->s, params->c, pos.start);
		if (pos.end == pos.start)
			break ;
		if (!alloc_copy(params, pos, limit))
			return (0);
		limit++;
	}
	return (limit);
}

// SPLIT FOR MINISHEL PARAMETERS
char	**ft_minisplit(const char *s, char c)
{
	char	**split;
	size_t	limit;
	size_t	word_count;
	t_split	params;
	size_t	i;

	limit = 0;
	i = -1;
	word_count = ft_param_count(s, c);
	if (word_count == 0)
		return (NULL);
	split = malloc((word_count + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	while (++i <= word_count)
		split[i] = NULL;
	params.split = split;
	params.s = s;
	params.c = c;
	limit = wordcount(&params, limit);
	if (!limit)
		return (ft_free(split), NULL);
	split[limit] = NULL;
	return (split);
}

// MAIN
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
				prompts = ft_free(prompts); // Free allocated memory
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
}
