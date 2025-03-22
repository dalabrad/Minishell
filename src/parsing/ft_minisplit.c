#include "minishell_exec.h"
#include "minishell_parsing.h"

// IGNORE separat
static size_t	skip_separat(const char *s, char c, size_t pos)
{
	while (s[pos] == c && s[pos] != 0)
		pos++;
	return (pos);
}

// POSITION OF END OF PARAMETER
static t_parapos	param_end(const char *s, char c, size_t start)
{
	t_parapos	pos;

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
bool	allocpy(t_split *param, t_parapos pos, size_t idpara)
{
	param->split[idpara] = malloc(sizeof(char) * (pos.end - pos.start + 1));
	if (!param->split[idpara])
		return (false);
	ft_strlcpy_quote(param->split[idpara], param->s + pos.start, pos.end
		- pos.start + 1);
	return (true);
}

// SPLIT WORD COUNT FUNCTION
size_t	wordcount(t_split *param, size_t limit)
{
	t_parapos	pos;

	pos.start = 0;
	pos.end = 0;
	pos.in_quotes = false;
	pos.quote_char = '\0';
	while (param->split[limit] == NULL)
	{
		pos.start = skip_separat(param->s, param->c, pos.end);
		pos = param_end(param->s, param->c, pos.start);
		if (pos.end == pos.start)
			break ;
		if (!allocpy(param, pos, limit))
			return (0);
		limit++;
	}
	return (limit);
}

// SPLIT FOR MINISHEL PARAMETERS
char	**ft_minisplit(const char *s, char c)
{
	char **split;
	size_t limit;
	size_t word_count;
	t_split param;
	size_t i;

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
	param.split = split;
	param.s = s;
	param.c = c;
	limit = wordcount(&param, limit);
	if (!limit)
		return (ft_free(split), NULL);
	split[limit] = NULL;
	return (split);
}
