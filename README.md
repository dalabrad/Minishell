# Minishell

Minishell is a simplified UNIX shell implementation written in C as part of the 42 curriculum. It replicates the basic behavior of a shell: command parsing, pipes, redirection, environment variable expansion, and built-in command execution.

---

## Development

- Written in C using POSIX system calls
- Uses `readline` for user input
- Modules for parsing, execution, and environment

---

## Features

- Command execution with `PATH` resolution
- Built-in commands: `cd`, `pwd`, `echo`, `export`, `unset`, `env`, `exit`
- Input/output redirections: `>`, `>>`, `<`
- Pipes `|` to connect commands
- Environment variable expansion with `$VAR`
- Single and double quote handling
- Syntax error detection
- Exit code propagation
- Command history (via readline)

---

## Requirements

- Linux
- `gcc`
- `make`
- `readline` library

---

# Installation

## Compilation: Make rules

Compile the project by running `make` from your terminal. Available rules:

| Command        | Description                                                    |
|----------------|----------------------------------------------------------------|
| `make`         | Compiles the project and creates the `minishell` executable.   |
| `make gdb`     | Compiles the project with debug symbols (`-g3`).               |
| `make valgrind`| Compiles with `-g3` and useful flags for Valgrind testing.     |
| `make clean`   | Removes `.o` object files.                                     |
| `make fclean`  | Removes all executables and object files.                      |
| `make re`      | Equivalent to `fclean` followed by `make`.                     |
| `make testd`   | Compiles an execution-enabled version (`main_test_d`).         |
|----------------|----------------------------------------------------------------|
---

## Execution: Using the shell

Once compiled, run the shell with:

```bash
./minishell
```

Example:

```bash
minishell>> echo "Hello World" > out.txt | cat out.txt
```

To exit:

```bash
minishell>> exit
```

---

## Project Structure

minishell/
├── src/
│   ├── parsing/
│   ├── cmd_execution/
│   ├── built-ins/
│   ├── environment/
│   ├── error_messages/
│   └── minishell_data/
├── inc/
├── libft/
└── main.c

---

## Temporary Visual Output

Used during development to visualize parsed tokens:

```bash
=========== PIPE SEGMENTS ===========
PIPE[0]: echo "hello" > out.txt 
→ Token: echo            | Type: COMMAND     
→ Token: "hello"         | Type: ARG         
→ Token: >               | Type: RED_OUT     
→ Token: out.txt         | Type: ARG

PIPE[1]: ls -l
→ Token: ls              | Type: COMMAND
→ Token: -l              | Type: COMMAND

PIPE[2]: wc -l
→ Token: wc              | Type: COMMAND
→ Token: -l              | Type: COMMAND
```

---

## Testing

Scripts include automatic tests for:

- `testing_all.sh`         → GENERAL
- `testing_meta_error.sh`  → METACHARACTERS
- `testing_path_quotes.sh` → PATH & QUOTES
- `testing_redir_error.sh` → REDIRECTION ERRORS
- `testing_expansion.sh`   → VARIABLE EXPANSIONS

### Running Tests

Make script executable and run it:

```bash
chmod +x testing.sh
./testing.sh
```

A final summary of `PASS` and `FAIL` is displayed at the end.

---

### Internal Checks (ongoing improvements)

- Balanced quotes verification
- Token type classification (commands, paths, options, redirections)
- Syntax error handling

---

## Debugging and Valgrind

### Running with GDB:

```bash
make gdb
gdb ./minishell
```

Example `gdbinit_v.gdb` script:

```bash
break main
break ft_minisplit
break count_splitted
break split2array
break check_args_fixed
etc ...
```

Modify as needed.

### Running with Valgrind:

```bash
make valgrind
valgrind --leak-check=full ./minishell
```

---

## Cleanup

To remove temporary files:

```bash
make clean
```

To remove everything:

```bash
make fclean
```

---

## License

This project is part of 42 School curriculum, developed by:

    Vlorenzo and Dalabrad
    - https://github.com/Vlorenzolana
    - https://github.com/dalabrad

---

## Status

The project is under development, covering the essential shell features. Ready for advanced testing and future improvements.