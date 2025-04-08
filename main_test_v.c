/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_v.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:58:00 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/04/08 10:40:31 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "minishell_exec.h" */
#include "inc/minishell_parsing.h"

int	main(int argc, char **argv, char **envp)
{
	size_t i;
	size_t		i_pipes;
	size_t		j_pipes;
	size_t		fd;
	t_pipes	*args;
	t_pipes	*temp;
	t_pipes	*temp2;
	char	**res;
	char	*str_exit;
	t_pipes	*new_node;
	size_t i_words;
	(void)argv;
	(void)envp;

	new_node = NULL;
	new_node = init_struct(new_node);
	fd = 0;
	str_exit = "exit";
	i = 0;
	i_pipes = 0;
	j_pipes = 0;
	i_words = 0;
	if (argc != 1)
		return (printf("Too many arguments or readline failure.\n"), 0);
	args = NULL;
	args = init_struct(args);
	temp = args; // Guardamos HEAD
	temp2 = new_node;
	while (1)
	{
		i = 0;
		fd = dup(STDIN_FILENO);
		args = temp; // recuperamos HEAD
		args->str = readline(PROMPT);
		if (!ft_strcmp(args->str, str_exit)) // Salimos con "exit"
			break ;
		if (strchr(args->str, '|'))
			res = ft_minisplit(args->str, '|', &i_pipes); // i_pipes por REF
		else
		{
			i_pipes = 0;
			res = malloc(sizeof(char **)); // Alloc
			*res = args->str;
			if(is_open(*res))
			{
				write(1, "Syntax error\n", 14);
				continue;
			}
		}
		j_pipes = i_pipes + 1;        // i-words+1 devuelve tamaño de res**+NULL

		while (res && --j_pipes != 0) // recogemos j_pipes
		{
			new_node = malloc(sizeof(t_pipes));
			if (!new_node)
				return (1);
			new_node->str = res[i];
			printf(" ----> PRINTEO de I %zu\n", i);
			printf(" ----> PRINTEO de RES %s\n", res[i]);
			printf(" ----> PRINTEO de RES a NEW_NODE->STR %s\n", new_node->str);
			new_node->index = i++;
			/* new_node->next = NULL; */
			printf("----> INDEX %zu\n", new_node->index);
			printf("----> NODE[I] %s\n", new_node->str);
			if (new_node->str == NULL)
				break ;
			else
				if(ft_lstadd_front2(&new_node, new_node)) // añadir encima)
					break;
		}
		new_node = temp2;
		args = temp;
		while(args)
		{
			check_args(args->str, &i_words);
			printf("-----> I_WORDS %zu\n", i_words);
			args = args->next;
		}
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
