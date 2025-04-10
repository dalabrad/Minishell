#include "../inc/minishell_parsing.h"

void	print_tokens(t_tokens *token)
{
	int i = 0;
	while (token)
	{
		printf("TOKEN[%d]: \"%s\"\n", i++, token->str);
		token = token->next;
	}
}

void	free_tokens(t_tokens *tokens)
{
	t_tokens *tmp;
	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->str);
		free(tmp);
	}
}

//////////////////////////////////
// TEST SUITE
//////////////////////////////////

void	run_parser_tests(void)
{
	const char *tests[] = {
		"echo hello world",
		"ls -la | grep .c",
		"cat < infile | grep test > outfile",
		"echo \"Hello | world\" > file.txt",
		"wc -l << EOF",
		"mkdir test && cd test",
		"echo \"hola    mundo\"",
		NULL
	};

	printf("\n========== MINISHELL PARSER TESTS ==========\n");

	for (int i = 0; tests[i] != NULL; i++)
	{
		printf("\n[TEST %d] CMD: %s\n", i + 1, tests[i]);
		t_tokens *tokens = check_args_fixed(tests[i]);
		if (!tokens)
		{
			printf("-> ERROR parsing tokens.\n");
			continue;
		}
		print_tokens(tokens);
		free_tokens(tokens);
	}
}

//////////////////////////////////
// MAIN
//////////////////////////////////

int	main(void)
{
	run_parser_tests();
	return 0;
}
