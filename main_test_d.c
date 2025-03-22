/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:39:42 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/22 15:04:07 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*shell_envp;

	shell_envp = NULL;
	(void)argv;
	if (argc != 1)
	{
		printf("Error!!! Use:\n\t./minishell\n");
		return (EXIT_FAILURE);
	}
	if (shell_envp_create(envp, &shell_envp))
		return (EXIT_FAILURE);
	print_shell_envp(shell_envp);
	return (EXIT_SUCCESS);
}

//t_envp	*environ = NULL;

/* int	main(int argc, char **argv, char **envp)
{
	char	*arg[] = {"env", NULL};

	(void)envp;
	if (argc == 1)
	{
		printf("Error!!! Use:\n\t./minishell <command> <command_atribute>" \
			"<command_atribute>...\n");
		return (EXIT_FAILURE);
	}
	argv++;
	command_exec(argv);
	command_exec(arg);
	return (EXIT_SUCCESS);
} */

/* static size_t	arr_size(char **arr)
{
	size_t	len;

	len = 0;
	while (arr[len])
	{
		len++;
	}
	return (len);
}

static void	free_array(char	**arr, size_t arr_size)
{
	size_t	i;

	i = 0;
	while (i < arr_size)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free (arr);
	arr = NULL;
}

static void	print_array(char **arr, size_t arr_size)
{
	size_t	i;

	i = 0;
	while (i < arr_size)
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

int	main(void)
{
	char	*paths;
	char	**path_array;

	printf("Printing PATH variable...\n\n");
	paths = getenv("PATH");
	if (!paths)
		return (EXIT_FAILURE);
	printf("%s\n\n", paths);
	path_array = ft_split(paths, ':');
	if (!path_array)
		return (EXIT_FAILURE);
	printf("Printing paths...\n\n");
	print_array(path_array, arr_size(path_array));
	free_array(path_array, arr_size(path_array));
	return (EXIT_SUCCESS);
} */

/* 
-----------------SALIDA DEL PROGRAMA---------------------
Printing PATH variable...

/home/dalabrad/bin:/home/dalabrad/bin:/usr/local/sbin:/usr/local/bin:
/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin

Printing paths...

/home/dalabrad/bin
/home/dalabrad/bin
/usr/local/sbin
/usr/local/bin
/usr/sbin
/usr/bin
/sbin
/bin
/usr/games
/usr/local/games
/snap/bin */

/* 
// ----------------OLD VERSION------------------
int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	printf("Printing envp...\n\n");
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	return (EXIT_SUCCESS);
} */