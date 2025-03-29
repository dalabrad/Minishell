#include "minishell_exec.h"
#include "minishell_parsing.h"

//  CHECK IF OPEN QUOTES
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

// PARSING QUOTES FUNCTION
bool	in_out_quotes(const char *s, size_t *i, char c)
{
	bool	in_quotes;
	char	quote_char;

	in_quotes = false;
	quote_char = '\0';
	while (s[*i] != 0 && (s[*i] != c || in_quotes))
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

// COUNT PARAMETERS FUNCTION
size_t	ft_param_count(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != 0)
	{
		if (!is_open(s))
			exit(1);
		while (s[i] == c && s[i] != 0)
			i++;
		i = 0;
		if (s[i] != 0)
		{
			count++;
			in_out_quotes(s, &i, c);
		}
		i++;
	}
	return (count);
}

// STRING COPY BETWEEN SEPARTOR
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
