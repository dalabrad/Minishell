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
...
```

Desde ahí puedes acceder fácilmente a los tokens para ejecutar comandos.

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

## ERRORES COMUNES

- Asegúrate de que `check_args_fixed()` detecta correctamente las comillas.
- Verifica `pipe_segments[i] != NULL` antes de usarlo.
- Si ves `pipe_segments[n] is NULL`, probablemente `count_splitted()` esté contando mal.

---

## 🧪 RECOMENDACIONES PARA TESTEO

- Probar con `"`, `'`, `>`, `>>`, `<`, `<<`, `|`.
- Validar casos límite como:
  - Comillas no cerradas
  - Pipes vacíos
  - Espacios múltiples

---

## EXTRA: FUNCIONES ÚTILES

- `poly_substr()` — Separa palabras manejando comillas.
- `set_command_type()` — Decide qué token es el comando principal.
- `token_type_str()` — Devuelve string representativo del tipo de token.

---

## PARA EL EQUIPO DE EJECUCIÓN

Usar `tokens_by_segment[i]` como entrada para tu executor. Cada nodo `t_tokens` tiene:

```
char *str          // contenido
t_TokenType type   // tipo de token
int was_quoted     // entrecomillado
```

---