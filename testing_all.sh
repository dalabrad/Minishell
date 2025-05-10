#!/bin/bash

BIN=./minishell
NUM_RANDOM=30

commands=("echo" "ls" "cat" "grep" "wc" "awk" "sort" "head" "touch" "mkdir")
symbols=(">" ">>" "<" "<<" "|" "||" "&&" "<<<")
args=("file1" "file2" "infile" "outfile" "text" "then" "if" "done" "42" "*" "?")

declare -a TESTS=()

for i in $(seq 1 $NUM_RANDOM); do
    parts=()
    len=$((RANDOM % 6 + 3))
    for j in $(seq 1 $len); do
        case $((RANDOM % 4)) in
            0) parts+=("${commands[RANDOM % ${#commands[@]}]}") ;;
            1) parts+=("${args[RANDOM % ${#args[@]}]}") ;;
            2) parts+=("${symbols[RANDOM % ${#symbols[@]}]}") ;;
            3) parts+=("\"${args[RANDOM % ${#args[@]}]}") ;;
        esac
    done
    TESTS+=("$(IFS=' '; echo "${parts[*]}")")
done

TESTS+=(
    "echo 'unterminated
    echo \"unterminated
    '"
    "\""
    "echo \"\"\"\""
    "echo ''''"
    "echo \" ' \" ' \""
    "\"echo\" 'ls' > > < | << >>"
    "cat << EOF"
    "echo <<<<<<< HEAD"
    ">>>>"
    "echo hola >>> file"
    "ls >>>> file"
    "ls | | cat"
    "cat ||| echo"
    "echo hola &&&& ls"
    "echo || echo && ls >> >>"
    "echo hola <<< \"text\" >>>"
    "cat file <<< >>> file"
    "echo > < > <"
    "cat < < < < file"
    "echo | | |"
    "ls | > >"
    "| | |"
    ">"
    "<"
    "|"
    "echo |"
    "cat <"
    "ls >>"
    "echo hola >"
    "echo > >> > < < file"
    "echo < file > file < file > file | cat"
)


pass=0
fail=0
total=${#TESTS[@]}

echo "===== RUNNING $total FINAL TESTS ====="

for input in "${TESTS[@]}"; do
    echo -e "\n Input: $input"
    
    output=$(echo "$input" | $BIN 2>&1)
    exit_code=$?

    if [[ "$output" == *"Syntax error"* ]]; then
        echo "Syntax error correctamente detectado"
        ((pass++))
    elif [[ "$output" == *"PIPE SEGMENTS"* && "$input" =~ [\>\<\|] ]]; then
        echo "Error lógico: el input no debería parsearse como válido"
        ((fail++))
    elif [[ "$output" == *"PIPE SEGMENTS"* ]]; then
        echo "Parseo válido"
        ((pass++))
    elif [[ $exit_code -ne 0 ]]; then
        echo "Crash (exit $exit_code)"
        ((fail++))
    elif [[ "$output" == *"minishell>>"* ]]; then
        echo "Entrada ignorada o espera input multiline"
        ((pass++))
    else
        echo "Salida inesperada"
        echo "$output"
        ((fail++))
    fi
done

echo -e "\n========== SUMMARY =========="
echo -e "\n\033[1mResumen final:\033[0m"
echo -e "\033[32mPASS:\033[0m $pass"
echo -e "\033[31mFAIL:\033[0m $fail"

if [ "$fail" -eq 0 ]; then
    echo -e "\n\033[1;32mTodos los tests pasaron con éxito\033[0m"
else
    echo -e "\n\033[1;31mAlgunos tests fallaron. Revisa la salida arriba.\033[0m"
fi

rm -f "$TMP"
echo "============================="