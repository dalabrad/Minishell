# MINI-SHELL PARSER: GUÍA PARA COMPILAR, TESTEAR Y USAR TOKENS

Este documento describe cómo compilar, testear y utilizar el sistema de parsing de comandos de MiniShell. Está pensado para que cualquier miembro del equipo pueda probar el parser y utilizar los tokens generados para la fase de ejecución.

---

## ESTRUCTURA PRINCIPAL

- `main_test_v.c` — Función principal de testeo.
- `ft_minisplit.c` — Separa el input por pipes.
- `ft_clasifyTokens.c` — Clasifica cada palabra/token.
- `utils_parsing.c` — Funciones auxiliares (comprobación de comillas, espacios, etc).
- `utils_initClean.c` — Manejo de memoria.

---

## CÓMO COMPILAR

```bash
make testv
```

Este comando compilará tu Minishell con la función `main_test_v.c` para realizar pruebas.

---

## CÓMO EJECUTAR

```bash
./minishell
```

Y luego puedes introducir comandos como:

```bash
echo "hola mundo" > out.txt | ls -l | wc -l
```

---

## QUÉ HACE

1. Separa la entrada por `|`.
2. Tokeniza cada segmento de pipe.
3. Clasifica tokens como `COMMAND`, `ARG`, `RED_OUT`, etc.
4. Muestra información de cada token (incluyendo si estaba entre comillas).
5. Aplica reglas para decidir cuál token es el comando en cada pipe.

---

## SALIDA DE EJEMPLO

```bash
=========== PIPE SEGMENTS ===========
-----> Tokenizing: [echo "hola mundo" > out.txt]
→ Token: echo            | Type: COMMAND      | Quoted: no
→ Token: "hola mundo"    | Type: ARG          | Quoted: yes
→ Token: >               | Type: RED_OUT      | Quoted: no
→ Token: out.txt         | Type: ARG          | Quoted: no
Total tokens: 4

-----> Tokenizing: [ ls -l ]
→ Token: ls              | Type: COMMAND      | Quoted: no
→ Token: -l              | Type: OPTION       | Quoted: no
Total tokens: 2

-----> Tokenizing: [ wc -l]
→ Token: wc              | Type: COMMAND      | Quoted: no
→ Token: -l              | Type: OPTION       | Quoted: no
Total tokens: 2
```

---

## ACCESO A TOKENS

En la función `main_test_v.c`, cada grupo de tokens está guardado así:

```c
t_tokens **tokens_by_segment;
```

Esto es un array de listas enlazadas. Cada posición representa un pipe:

```c
tokens_by_segment[0] → tokens de primer pipe
tokens_by_segment[1] → tokens de segundo pipe
```


Desde ahí puedes acceder fácilmente a los tokens para ejecutar comandos.

### ¿Dónde están los tokens listos para ejecutar?
Después del ft_minisplit(), se llama a:

```c
tokens_by_segment[i] = check_args_fixed(pipe_segments[i], &segment_tokens);
```

Entonces:

```c
// tokens_by_segment[i] contiene la lista enlazada de tokens del PIPE[i]
```

Cada t_tokens tiene:

str: el string del token

type: tipo de token (COMMAND, ARG, RED_OUT, etc.)

was_quoted: si venía entre comillas

Ejemplo:
Si quieres ejecutar el primer pipe, podés hacer:

```c
t_tokens *cmd = tokens_by_segment[0];
while (cmd)
{
    printf("TOKEN: %s | TIPO: %d\n", cmd->str, cmd->type);
    cmd = cmd->next;
}
```

---

### Tipos de token (t_TokenType)

```c
typedef enum t_TokenType {
	RED_IN,
	RED_OUT,
	HEREDOC,
	APPEND_OUT,
	OPTION,
	COMMAND,
	SETTING,
	ARG,
	ERROR
} t_TokenType;
```

---

Siguiente paso: ejecución
A partir de los tokens de tokens_by_segment[i]:

El primer token con tipo COMMAND es el comando principal.

Los de tipo ARG, OPTION, etc. van a argv[].

Si hay redirecciones (RED_OUT, HEREDOC, etc.), puedes guardar el filename (token->next->str) y aplicar dup2() después.

### Consejo para integración
Puedes construir estructuras tipo:

```c
typedef struct s_exec_cmd {
    char **argv;           // ["echo", "hola", NULL]
    char *outfile;         // si hay redirección >
    char *infile;          // si hay redirección <
    int append;            // si es >>
} t_exec_cmd;
```

Y llenar estos valores recorriendo la lista de tokens_by_segment[i].

---

## LIMPIEZA DE MEMORIA

Al final del ciclo, los tokens y pipe_segments se liberan correctamente:

```c
free_array2(pipe_segments);
for (size_t j = 0; j <= i_pipes; j++)
    free_tokens_list(tokens_by_segment[j]);
free(tokens_by_segment);
```

---

## DEBUGGING CON GDB

```bash
make gdb
```

- Probar con `"`, `'`, `>`, `>>`, `<`, `<<`, `|`.
- Validar casos límite como:
  - Comillas no cerradas
  - Pipes vacíos
  - Espacios múltiples
- Probar a cambiar el archivo config GDB para hacer breakpoints en mas funciones.

---

## EXTRA: FUNCIONES ÚTILES

- `poly_substr()` — Separa palabras manejando comillas.
- `set_command_type()` — Decide qué token es el comando principal.
- `token_type_str()` — Devuelve string representativo del tipo de token.

---

## PARA PARTE DE EJECUCIÓN

Usar `tokens_by_segment[i]` como entrada para tu ejecutor. Cada nodo `t_tokens` tiene:

```
char *str          // contenido
t_TokenType type   // tipo de token
int was_quoted     // entrecomillado
```

---