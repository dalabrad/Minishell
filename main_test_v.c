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

#include "minishell_exec.h"
#include "minishell_parsing.h"

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
}
