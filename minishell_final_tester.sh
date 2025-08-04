#!/bin/bash

MINISHELL=./minishell
GREEN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m"

OUTFILE=minishell_output.txt

run_test() {
    local description="$1"
    local input="$2"
    local expected="$3"

    echo -e "\n${GREEN}>> Test: $description${NC}"
    echo -e "$input" | $MINISHELL > "$OUTFILE" 2>&1

    if grep -q "$expected" "$OUTFILE"; then
        echo -e "${GREEN}✓ Passed${NC}"
    else
        echo -e "${RED}✗ Failed${NC}"
        echo "Expected: $expected"
        echo "Got:"
        cat "$OUTFILE"
    fi
}

####### TESTS ########

# 1. Comando simple
run_test "Simple comando absoluto" "/bin/ls" ""

# 2. Argumentos
run_test "echo con argumentos" "echo hola mundo" "hola mundo"
run_test "ls con argumento" "ls /tmp" ""

# 3. echo
run_test "echo sin salto de línea" "echo -n hola" "hola"

# 4. exit
run_test "exit con código" "exit 42" ""

# 5. Valor de retorno
run_test "echo $? tras éxito" "/bin/ls\necho \$?" "0"
run_test "echo $? tras error" "/bin/ls noexiste\necho \$?" "1"

# 6. Comillas dobles
run_test "echo con comillas dobles" "echo \"Hola Mundo\"" "Hola Mundo"
run_test "echo \$USER en comillas dobles" "export USER=vanessa\necho \"Hola \$USER\"" "Hola vanessa"

# 7. Comillas simples
run_test "echo con comillas simples" "echo '\$USER'" "\$USER"
run_test "echo texto con espacios entre comillas simples" "echo 'uno dos tres'" "uno dos tres"

# 8. Variables de entorno
run_test "export y echo \$VAR" "export VAR=42\necho \$VAR" "42"
run_test "unset y comprobar \$VAR" "unset VAR\necho \$VAR" ""

# 9. pwd y cd
run_test "pwd básico" "pwd" "$(pwd)"
run_test "cd / y pwd" "cd /\npwd" "/"

# 10. Redirecciones
run_test "redirección >" "echo hola > out.txt\ncat out.txt" "hola"
run_test "redirección >>" "echo hola > file.txt\necho mundo >> file.txt\ncat file.txt" "mundo"
run_test "redirección <" "echo entrada > in.txt\ncat < in.txt" "entrada"

# 11. Pipes
run_test "echo piped a grep" "echo hola mundo | grep hola" "hola mundo"
run_test "doble pipe" "echo hola mundo | grep mundo | cat" "hola mundo"
run_test "pipe y redirección" "echo hola mundo | grep hola > p.txt\ncat p.txt" "hola mundo"

# 12. Comando inválido
run_test "comando inexistente" "cmdinvalido" "command not found"

# 13. PATH
run_test "ls con PATH válido" "ls" ""
run_test "ls sin PATH" "unset PATH\nls" "command not found"
run_test "reexportar PATH" "export PATH=/bin:/usr/bin\nls" ""

# 14. Here-doc (entrada estándar simulada)
run_test "heredoc básico" "cat << EOF\nlinea1\nEOF" "linea1"

# 15. Variables con comillas combinadas
run_test "echo \"\'$USER'\" combinado" "export USER=vanessa\necho \"'\$USER'\"" "'vanessa'"

# 16. Caso extremo: comando largo
run_test "echo comando largo" "echo $(yes arg | head -n 30)" "arg"

# Limpieza
rm -f "$OUTFILE" out.txt file.txt in.txt p.txt

echo -e "\n${GREEN}Todos los tests ejecutados.${NC}"
