# Minishell

## Descripción
Minishell es una versión simplificada de un shell de Unix creada como parte del currículum de 42. El proyecto busca replicar el comportamiento de un shell real, manejando la ejecución de comandos, redirecciones, pipes, variables de entorno y funciones incorporadas, cumpliendo con las restricciones del proyecto.

## Características
- Muestra un prompt y espera la entrada del usuario
- Ejecuta comandos simples con argumentos
- Maneja variables de entorno (expansión `$VAR`)
- Implementa comandos internos:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Soporta redirecciones de entrada y salida (`>`, `>>`, `<`)
- Implementa pipes (`|`) para encadenar comandos
- Maneja señales como `Ctrl+C`, `Ctrl+D` y `Ctrl+\`
- Manejo de errores y gestión adecuada de memoria

## Instalación
### Requisitos previos
Asegúrate de tener **GNU Make** y un **compilador de C (gcc o clang)** instalado.

### Compilar
```sh
make
```
Esto generará el ejecutable `minishell`.

### Ejecutar
```sh
./minishell
```

## Uso
Una vez dentro de **minishell**, puedes ejecutar comandos como en un shell estándar. Ejemplo:
```sh
$ echo "¡Hola, Mundo!"
¡Hola, Mundo!
$ ls -l | grep minishell
$ export MI_VAR=42
$ echo $MI_VAR
42
$ exit
```

## Desarrolladores
- **dalabrad**  
- **vlorenzolana**

## Licencia
Este proyecto ha sido desarrollado como parte del currículo de 42 y sigue sus normas de integridad académica. Úsalo y modifícalo bajo tu propia responsabilidad.

