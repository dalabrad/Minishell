#!/bin/bash

BIN=./minishell 
TMP=out.tmp
pass=0
fail=0

valid_cmds=("ls" "echo hello" "cat file.txt" "grep txt" "pwd" "env" "whoami")

ops=("||" "<<<" ">>>" "><" "|>" ">|" ">>|" "|||" "><<" "<<>>" "> >" "< <" "| |")

num_tests=50

generate_random_input() {

    case $((RANDOM % 4)) in
        0) echo "${valid_cmds[RANDOM % ${#valid_cmds[@]}]} ${ops[RANDOM % ${#ops[@]}]}" ;;
        1) echo "${ops[RANDOM % ${#ops[@]}]} ${valid_cmds[RANDOM % ${#valid_cmds[@]}]}" ;;
        2) echo "${valid_cmds[RANDOM % ${#valid_cmds[@]}]} ${ops[RANDOM % ${#ops[@]}]} ${valid_cmds[RANDOM % ${#valid_cmds[@]}]}" ;;
        3) echo "${ops[RANDOM % ${#ops[@]}]}" ;;
    esac
}

for i in $(seq 1 $num_tests); do
    input=$(generate_random_input)
    echo -e "\n[$i] Entrada: '$input'"

    echo "$input" | $BIN > "$TMP" 2>&1
    exit_code=$?
    output=$(<"$TMP")

    if [[ "$output" == *"Syntax error"* && $exit_code -eq 0 ]]; then
        echo "PASS: Syntax error detectado correctamente"
        ((pass++))
    elif [[ $exit_code -ge 128 ]]; then
        echo "FAIL: Crash del binario (exit code $exit_code)"
        cat "$TMP"
        ((fail++))
    elif [[ "$output" != *"Syntax error"* && "$output" != *"minishell>>"* ]]; then
        echo "FAIL: Salida inesperada sin 'Syntax error' ni prompt"
        cat "$TMP"
        ((fail++))
    else
        echo "FAIL: Salida no detectó el error de sintaxis aunque era inválido"
        cat "$TMP"
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