/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:39:42 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/15 13:11:27 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

/* int	main(int argc, char **argv, char **envp)
{
	t_env	*shell_envp;
	int		status = 0;
	pid_t	pid;

	if (argc == 1)
	{
		printf("Error!!! Use:\n\t./minishell <command> <command_atribute> " \
			"<command_atribute>...\n");
		return (EXIT_FAILURE);
	}
	shell_envp = NULL;
	if (shell_envp_list_create(envp, &shell_envp))
		return (EXIT_FAILURE);
	argv++;
	printf("\n=======================================================\n\n");
	pid = fork();
	if (pid == -1)
	{
		printf("minishel: could not fork process\n");
		return (EXIT_FAILURE);
	}
	else if (!pid)
		status += command_exec(argv, &shell_envp);
	else
	{
		waitpid(pid, NULL, 0);
		printf("\n========================================================\n\n");
	}
	free_shell_envp_list(&shell_envp);
	return (status);
} */

/* int	main(int argc, char **argv, char **envp)
{
	char	*str_exit = "exit";
	char	*line;
	char	**pipe_segments;
	size_t	i_pipes;
	size_t	i;
	t_tokens **tokens_by_segment;
	t_env	*shell_envp;
	pid_t	pid;

	(void)argv;
	(void)envp;

	if (argc != 1)
	{
		return (printf("Too many arguments or readline failure.\n"), 0);
	}
	shell_envp = NULL;
	if (shell_envp_list_create(envp, &shell_envp))
		return (EXIT_FAILURE);
	while (1)
	{
		line = readline(PROMPT);
		// fd, open, dup
		// fd = dup(STDIN_FILENO);
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (!ft_strcmp(line, str_exit))
		{
			free(line);
			break; 
		}

		pipe_segments = ft_minisplit(line, '|', &i_pipes);
		if (!pipe_segments)
		{
			free(line);
			continue;
		}

		tokens_by_segment = malloc(sizeof(t_tokens *) * (i_pipes + 1));
		if (!tokens_by_segment)
		{
			perror("malloc tokens_by_segment");
			free_array2(pipe_segments);
			free(line);
			continue;
		}

		for (size_t i = 0; i < i_pipes; i++)
			tokens_by_segment[i] = NULL;

		printf("\n=========== PIPE SEGMENTS ===========\n");
		i = 0;
		while (i < i_pipes)
		{
			if (!pipe_segments[i])
			{
				fprintf(stderr, "Error: pipe_segments[%zu] is NULL\n", i);
				tokens_by_segment[i] = NULL;
				i++;
				continue;
			}

			size_t segment_tokens = 0;
			tokens_by_segment[i] = check_args_fixed(pipe_segments[i], &segment_tokens);
			if (!tokens_by_segment[i])
			{
				fprintf(stderr, "Warning: could not tokenize segment %zu\n", i);
			}
			else
			{
				// FIRST ARG AS COMMAND
				set_command_type(tokens_by_segment[i]);
				print_tokens(tokens_by_segment[i]);
			}
			printf("Total tokens checking-process: %zu\n\n", segment_tokens);
			i++;
		}

		i = 0;
		while (i < i_pipes)
		{
			char	**args = NULL;

			args = tokens_to_args(tokens_by_segment[i]);
			print_array(args);
			// EJEcución del comando.
			printf("\n========================================================\n\n");
			pid = fork();
			if (pid == -1)
			{
				printf("minishel: could not fork process\n");
				return (EXIT_FAILURE);
			}
			else if (!pid)
				command_exec(args, &shell_envp);
			else
			{
				waitpid(pid, NULL, 0);
			printf("\n========================================================\n\n");
			}
			free_array(args);
			i++;
		}

		free_array2(pipe_segments);
		if (tokens_by_segment)
		{
			for (size_t j = 0; j < i_pipes; j++)
				if (tokens_by_segment[j])
					free_tokens_list(tokens_by_segment[j]);
			free(tokens_by_segment);
		}
		free(line);
		// close fd
	}
	free_shell_envp_list(&shell_envp);
	return (0);
} */

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	pid_t	pid;

	if (argc == 1)
	{
		printf("Error!!! Use:\n\t./minishell <command> <command_atribute> " \
			"<command_atribute>...\n");
		return (EXIT_FAILURE);
	}
	if (data_init(&data, envp))
		return (EXIT_FAILURE);
	argv++;
	printf("\n=======================================================\n\n");
	pid = fork();
	if (pid == -1)
	{
		printf("minishel: could not fork process\n");
		return (EXIT_FAILURE);
	}
	else if (!pid)
		command_exec(argv, data);
	else
	{
		waitpid(pid, NULL, 0);
		printf("\n========================================================\n\n");
	}
	free_data(&data);
	return (EXIT_SUCCESS);
}