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

## License

This project is part of 42 School curriculum, developed by:

    Vlorenzo and Dalabrad
    - https://github.com/Vlorenzolana
    - https://github.com/dalabrad

---

## Status

The project is under development, covering the essential shell features. Ready for advanced testing and future improvements.