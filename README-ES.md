# Minishell

Minishell es una implementación simplificada de una shell UNIX escrita en C como parte del currículo de 42. Replica el comportamiento básico de una shell: parsing de comandos, pipes, redirecciones, expansión de variables de entorno y ejecución de comandos built-in.

---

## Desarrollo

- Escrito en C usando llamadas POSIX
- Utiliza `readline` para entrada del usuario
- Módulos para parsing, ejecución y entorno

---

## Funcionalidades

- Ejecución de comandos con resolución de rutas (`PATH`)
- Comandos internos: `cd`, `pwd`, `echo`, `export`, `unset`, `env`, `exit`
- Redirecciones de entrada/salida: `>`, `>>`, `<`
- Pipes `|` para enlazar comandos
- Expansión de variables de entorno `$VAR`
- Manejo de comillas simples y dobles
- Detección de errores de sintaxis
- Propagación del código de salida
- Historial de comandos (readline)

---

## Requisitos

- Linux
- `gcc`
- `make`
- Biblioteca `readline`

---
# Instalacion

## Compilacion: reglas de Make

Compila el proyecto introduciendo `make` por tu Terminal. También existen las siguientes reglas:

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

## Ejecución: como se usa nuestra mini

Una vez compilado, puedes iniciar la minishell con:
## Ejecución

Una vez compilado, puedes iniciar la minishell con:

```bash
make run
```

o

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

## Como lanzar el testeo

Haz ejecutable el script y ejecútalo:

```bash
chmod +x testing.sh
./testing.sh
```

Resumen final de `PASS` y `FAIL` al final de la ejecución.

---

### Comprobaciones, sujetas a mejoras futuras
- Comprobación de comillas balanceadas
- Clasificación de tipos de token (comandos, paths, opciones, redirecciones)
- Manejo de errores de sintaxis

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
etc..
```
Editar en funcion de necesidad.

### Ejecutar con Valgrind:

```bash
make valgrind
valgrind --leak-check=full ./minishell
```

## Estructura del Proyecto


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

## Licencia

Este proyecto forma parte del currículo de la escuela 42 desarrollado por:

    Vlorenzo y Dalabrad 
	.	https://github.com/dalabrad
	.	https://github.com/Vlorenzolana


---

## Estado

El proyecto está en desarrollo, cubre los fundamentos básicos de un shell. Está listo para pruebas más complejas y mejoras futuras.

---
