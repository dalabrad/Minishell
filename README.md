# Minishell

Basic implementation of a C shell according to the 42 School project. Supports command execution, redirects, pipes, argument parsing, etc.

---

## Requirements

- Linux
- `gcc`
- `make`
- Library `readline`

---

## Make rules

You can compile the project with the following rules:

| Command         | Description                                                           |
|-----------------|-----------------------------------------------------------------------|
| `make`          | Compiles the project and generates the `minishell` executable.        |
| `make gdb`      | Compile the project with debugging symbols (`-g3`).                   |
| `make valgrind` | Compile with `-g3` and flags useful for executing with Valgrind.      |
| `make clean`    | Remove `.o` files.                                                    |
| `make fclean`   | Remove executables and `.o` files.                                    |
| `make re`       | Equivalent to `fclean` followed by `make`.                            |
| `make testd`    | Compile a version that includes EXECUTE (`main_test_d`).              |
---

## Execution
<<<<<<< HEAD
=======

Once compiled, you can start the minishell with:
>>>>>>> 16548874b2eafe0096e0bd6b1e43a87279e9e2f0

Once compiled, you can start the minishell with:

```bash
./minishell
```

Example usage:

<<<<<<< HEAD
```bash
minishell>> echo ‘Hello World’ > out.txt | cat out.txt
```

To exit:

```bash
minishell>> exit
```

---

## Visualization

Result on screen:

```bash
=========== PIPE SEGMENTS ===========
PIPE[0]: echo "hola" > out.txt 
→ Token: echo            | Type: COMMAND     
→ Token: "hola"          | Type: ARG         
→ Token: >               | Type: RED_OUT     
→ Token: out.txt         | Type: ARG

PIPE[1]: ls -l
→ Token: ls              | Type: COMMAND
→ Token: -l              | Type: COMMAND (it's OPTION but for exec better COMMAND)

PIPE[2]: wc -l
→ Token: wc              | Type: COMMAND
→ Token: -l              | Type: COMMAND (it's OPTION but for exec better COMMAND)
```
---

## Testing

Tesing script tests:
- `testing_all.sh`         → GENERAL
- `testing_meta_error.sh`  → METACHARS
- `testing_path_quotes.sh` → PATH/BALANCING
- `testing_redir_error.sh` → ERROR
- `testing_expansion.sh` → EXPANSIONS

Command: bash `yourtest.sh`
---

# Accessing Tokens in Minishell to Execute Commands

This document explains how to access and use parser-generated tokens in `minishell` to execute commands correctly.

---

## Objective

Traverse the **tokens** of each `pipe_segment` and build `argv[]` to execute commands using `execve` or `execvp`.

---

## How to access tokens

Each entry in `tokens_by_segment[i]` is the head of a linked list of `t_tokens`:

```c
t_tokens **tokens_by_segment; // linked list array
size_t i_pipes; // number of pipes
````
=======
````bash
minishell>> echo ‘Hello World’ > out.txt | cat out.txt
```

To exit:

````bash
minishell>> exit
```

---

## Testing

The script includes automated testing for:
- `testing_all.sh` → Automated testing script GENERAL
- testing_meta_error.sh` → automated testing script METACARACTERES
- `testing_p
>>>>>>> 16548874b2eafe0096e0bd6b1e43a87279e9e2f0

Cycles through tokens using `while`:

```c
size_t i = 0;

while (i < i_pipes)
{
t_tokens *current = tokens_by_segment[i];
	
	while (current)
{
printf("Token string: %s\n", current->str);
printf("Token type : %d\n", current->type); // You can use token_type_str()
current = current->next;
}
i++;
}
```

---

## What to do with each token

- The first token type `COMMAND` is the command.
- Tokens of type `ARG` and `OPTION` are the arguments.

You can construct a `char *argv[]` to pass to `execve`:

---

## Example: construct `argv[]`.

```c
char **build_argv(t_tokens *tokens)
{
	size_t count = 0;
	t_tokens *tmp = tokens;

	// contar argumentos
	while (tmp)
	{
		if (tmp->type == COMMAND || tmp->type == ARG || tmp->type == OPTION)
			count++;
		tmp = tmp->next;
	}

	char **argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return NULL;

	tmp = tokens;
	size_t i = 0;
	while (tmp)
	{
		if (tmp->type == COMMAND || tmp->type == ARG || tmp->type == OPTION)
		{
			argv[i] = tmp->str;  // o strdup(tmp->str)
			i++;
		}
		tmp = tmp->next;
	}
	argv[i] = NULL;
	return argv;
}
```

---

## Execute command

```c
char **argv = build_argv(tokens_by_segment[i]);

if (argv && argv[0])
execvp(argv[0], argv); // or execve()

// free argv if you did strdup()
````

---

## Conclusion

- Use `tokens_by_segment[i]` to access tokens.
- Use `while` to traverse the linked list.
- Build `argv[]` with `COMMAND`, `ARG` and `OPTION`.
- Execute with `execvp` or `execve`.

---