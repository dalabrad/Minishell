#!/bin/bash

BIN=./minishell

NUM_RANDOM=20

declare -a TESTS=(
    ">"
    "<"
    ">>"
    "<<"
    "<<<"

    "echo hola >"
    "ls >>"
    "cat <"
    "echo hola <<<"

    "echo hola > >"
    "cat < < file"
    "ls >>> file"
    "echo hola >> > file"
    "echo hola > >> file"
    "echo hola < > file"
    "echo hola > < file"
    "echo hola < < infile"
    "ls >> >> outfile"

    "echo hola >   "
    "cat <     "
    "ls >>   "
    "echo >>    "

    "echo | >"
    "ls > | file"
    "cat < >"
    "cat << >>"

    "> > >"
    "< < <"
    ">> >> >>"
    "< > < >"
    "ls | > > > file"
    "ls > > file | cat"

    ">>>>"
    "<<< infile"
    "<<< >>>"
    "< < > >"
    ">>> <<<"
    "echo > > < < file"
)

commands=("echo" "ls" "cat" "grep" "wc" "awk" "sort")
symbols=(">" ">>" "<" "<<" "<<<" "|")
args=("file1" "file2" "infile" "outfile" "text" "then" "if")

for i in $(seq 1 $NUM_RANDOM); do
    c="${commands[RANDOM % ${#commands[@]}]}"
    s1="${symbols[RANDOM % ${#symbols[@]}]}"
    a1="${args[RANDOM % ${#args[@]}]}"
    if (( RANDOM % 2 )); then
        s2="${symbols[RANDOM % ${#symbols[@]}]}"
        a2="${args[RANDOM % ${#args[@]}]}"
        TESTS+=("$c $s1 $a1 $s2 $a2")
    else
        TESTS+=("$c $s1 $a1")
    fi
done

total=${#TESTS[@]}
pass=0
fail=0

echo "===== RUNNING $total TESTS ====="

for input in "${TESTS[@]}"; do
    echo -e "\nTest: $input"
    
    output=$(echo "$input" | $BIN 2>&1)
    exit_code=$?

    if [[ "$output" == *"Syntax error"* ]]; then
        echo "Syntax error detectado (válido)"
        ((pass++))
    elif [[ "$output" == *"minishell>>"* && "$output" != *"Syntax error"* && "$output" != *"PIPE SEGMENTS"* ]]; then
        echo "Entrada ignorada, sigue esperando (válido)"
        ((pass++))
    elif [[ $exit_code -ne 0 ]]; then
        echo "Crash o segfault (exit code $exit_code)"
        ((fail++))
    else
        echo "Salida inesperada:"
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