# Minishell

Implementación básica de un shell en C conforme al proyecto de 42 School. Soporta ejecución de comandos, redirecciones, pipes, parsing de argumentos, etc.
#### Guia de acceso a Tokens en Minishell para Ejecutar Comandos

---

## Requisitos

- Linux
- `gcc`
- `make`
- Biblioteca `readline`

---

## Reglas de Make

Puedes compilar el proyecto con las siguientes reglas:

| Comando            | Descripción                                                 |
|--------------------|-------------------------------------------------------------|
| `make`             | Compila el proyecto y genera el ejecutable `minishell`.     |
| `make gdb`         | Compila el proyecto con símbolos de depuración (`-g3`).     |
| `make valgrind`    | Compila con `-g3` y flags útiles para ejecutar con Valgrind.|
| `make clean`       | Elimina los archivos `.o`.                                  |
| `make fclean`      | Elimina ejecutables y archivos `.o`.                        |
| `make re`          | Equivalente a `fclean` seguido de `make`.                   |
| `make main_test_d` | Compila una versión que incluye EJECUCION (`main_test_d`).  |
|--------------------|-------------------------------------------------------------|
---

## Ejecución

Una vez compilado, puedes iniciar la minishell con:

```bash
./minishell
```

Ejemplo de uso:

```bash
minishell>> echo "Hola Mundo" > out.txt | cat out.txt
```

Para salir:

```bash
minishell>> exit
```

---

## Testing

Los script incluye pruebas automáticas para:
- `testing_all.sh`         → Script testeo automatizado GENERAL
- `testing_meta_error.sh`  → Script testeo automatizado METACARACTERES
- `testing_path_quotes.sh` → Script testeo automatizado PATH&BALANCEO
- `testing_redir_error.sh` → Script testeo automatizado ERROR

### Comprobaciones, sujetas a mejoras futuras
- Comprobación de comillas balanceadas
- Clasificación de tipos de token (comandos, paths, opciones, redirecciones)
- Manejo de errores de sintaxis

### Cómo usar el testing

Haz ejecutable el script y ejecútelo:

```bash
chmod +x testing.sh
./testing.sh
```

Resumen final de `PASS` y `FAIL` al final de la ejecución.

---

## Debugging y Valgrind

### Ejecutar con GDB:

```bash
make gdb
gdb ./minishell
```
Referencia a archivo gdbinit_v.gdb, con breapoints:
```bash
break main
break ft_minisplit
break count_splitted
break split2array
break check_args_fixed
```
Editar en funcion de necesidad.

### Ejecutar con Valgrind:

```bash
make valgrind
valgrind --leak-check=full ./minishell
```

---

## Versión de testing Dalabrad: `main_test_d`

Puedes compilar una versión especial de minishell enfocada en ejecucion:

```bash
make main_test_d
./main_test_d
```

Esto activa salidas especiales para verificación y ejecucion de tokens.

---

## Estructura del Proyecto
### Main
- `main.c` → Loop principal llamada a READLINE
### Parsing
- `ft_clasifyTokens.c` → Clasificación de tokens
- `ft_process_segments.c` → Parsing por segmentos
- `utils_*.c` → Funciones auxiliares (init, clean, print)
### Array Utils
- `array_utils.c`
### Built-ins
- `built-in_cd.c`
- `built-in_echo.c`
- `built-in_env.c`
- `built-in_exit.c`
- `built-in_export.c`
- `built-in_pwd.c`
- `built-in_unset.c`
### Command Execution
- `tokens_to_args.c`
- `command_exec.c`
### Environment
- `envp_attribute_getters.c`
- `shell_envp_list_create.c`
- `shell_envp_list_utils_1.c`
- `shell_envp_list_utils_2.c`
### Error Messages
### Minishell Data
- `minishell_data.c`

### Testing
- `testing_all.sh`         → Script testeo automatizado GENERAL
- `testing_meta_error.sh`  → Script testeo automatizado METACARACTERES
- `testing_path_quotes.sh` → Script testeo automatizado PATH&BALANCEO
- `testing_redir_error.sh` → Script testeo automatizado ERROR

---

## Limpieza

Para limpiar archivos temporales:

```bash
make clean
```

Para limpiar todo:

```bash
make fclean
```

---

## Estado

El proyecto está en desarrollo por David Labrador Garcia y Vanessa Lorenzo Toquero, cubre los fundamentos básicos de un shell. Está listo para pruebas más complejas y mejoras futuras.

---

# Acceso a Tokens en Minishell para Ejecutar Comandos

Este documento explica cómo acceder y usar los tokens generados por el parser en `minishell` para ejecutar comandos correctamente.

---

## Objetivo

Recorrer los **tokens** de cada `pipe_segment` y construir `argv[]` para ejecutar comandos usando `execve` o `execvp`.

---

## 🔍 Cómo acceder a los tokens

Cada entrada de `tokens_by_segment[i]` es la cabeza de una lista enlazada de `t_tokens`:

```c
t_tokens **tokens_by_segment;  // arreglo de listas enlazadas
size_t i_pipes;                // número de pipes
```

Recorre los tokens usando `while`:

```c
size_t i = 0;

while (i < i_pipes)
{
	t_tokens *current = tokens_by_segment[i];
	
	while (current)
	{
		printf("Token string: %s\n", current->str);
		printf("Token type  : %d\n", current->type);  // Puedes usar token_type_str()
		current = current->next;
	}
	i++;
}
```

---

## Qué hacer con cada token

- El primer token tipo `COMMAND` es el comando.
- Tokens tipo `ARG` y `OPTION` son los argumentos.

Puedes construir un `char *argv[]` para pasarlo a `execve`:

---

## 📦 Ejemplo: construir `argv[]`

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

## ⚖️ Ejecutar comando

```c
char **argv = build_argv(tokens_by_segment[i]);

if (argv && argv[0])
	execvp(argv[0], argv);  // o execve()

// libera argv si hiciste strdup()
```

---

## ✅ Conclusión

- Usa `tokens_by_segment[i]` para acceder a los tokens.
- Usa `while` para recorrer la lista enlazada.
- Construye `argv[]` con `COMMAND`, `ARG` y `OPTION`.
- Ejecuta con `execvp` o `execve`.

---

¡Ahora estás listo para conectar el parser con la ejecución!