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

| Command---------|---------Description---------------------------------------------------|
|-----------------|-----------------------------------------------------------------------|
| `make`          | Compiles the project and generates the `minishell` executable.        |
| `make gdb`      | Compile the project with debugging symbols (`-g3`).                   |
| `make valgrind` | Compile with `-g3` and flags useful for executing with Valgrind.      |
| `make clean`    | Remove `.o` files.                                                    |
| `make fclean`   | Remove executables and `.o` files.                                    |
| `make re`       | Equivalent to `fclean` followed by `make`.                            |
| `make testd`    | Compile a version that includes EXECUTE (`main_test_d`).              |
|-----------------|-----------------------------------------------------------------------|

---

## Execution

Once compiled, you can start the minishell with:

````bash
./minishell
```

Example usage:

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

Translated with DeepL.com (free version)