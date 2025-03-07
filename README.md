# Minishell

## Overview
Minishell is a simplified Unix shell created as part of the 42 curriculum. The project aims to replicate the behavior of a real shell, handling command execution, redirections, pipes, environment variables, and built-in functions while adhering to the specified project constraints.

## Features
- Display a prompt and wait for user input
- Execute simple commands with arguments
- Handle environment variables (`$VAR` expansion)
- Implement built-in commands:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Support input and output redirections (`>`, `>>`, `<`)
- Implement pipes (`|`) for command chaining
- Handle signals like `Ctrl+C`, `Ctrl+D`, and `Ctrl+\`
- Error handling and proper memory management

## Installation
### Prerequisites
Ensure you have **GNU Make** and a **C compiler (gcc or clang)** installed.

### Build
```sh
make
```
This will generate the `minishell` executable.

### Run
```sh
./minishell
```

## Usage
Once inside **minishell**, you can execute commands just like in a standard shell. Example:
```sh
$ echo "Hello, World!"
Hello, World!
$ ls -l | grep minishell
$ export MY_VAR=42
$ echo $MY_VAR
42
$ exit
```

## Developers
- **dalabrad**  
- **vlorenzolana**

## License
This project is developed as part of the 42 curriculum and follows its academic integrity guidelines. Use and modify at your own discretion!

