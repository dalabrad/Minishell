#!/bin/bash

BIN=./minishell 
MAX=10          
TMP=out.tmp

pass=0
fail=0

for ((i=1; i<=MAX; i++)); do
    input=""
    for ((j=1; j<=i; j++)); do
        input+="\""
    done

    echo -e "\n\033[1;34mTest con $i comillas:\033[0m \"$input\""

    echo "$input" | $BIN > "$TMP" 2>&1
    exit_code=$?
    output=$(<"$TMP")

    quote_count=$(grep -o '"' <<< "$input" | wc -l)
    remainder=$((quote_count % 2))

    if [[ $remainder -eq 0 ]]; then
        expected_output="=========== PIPE SEGMENTS ==========="
    else
        expected_output="Syntax error"
    fi

    if [[ "$output" == *"$expected_output"* ]]; then
        if [[ "$expected_output" == "=========== PIPE SEGMENTS ===========" ]]; then
            echo -e "\033[32mPASS:\033[0m Salida balanceada - Tokenización correcta (esperado: $expected_output)"
        else
            echo -e "\033[32mPASS:\033[0m Salida desbalanceada - Error de sintaxis (esperado: $expected_output)"
        fi
        ((pass++))
    elif [[ "$output" == *"Syntax error"* || "$output" == *"=========== PIPE SEGMENTS ==========="* ]]; then
        echo -e "\033[31mFAIL:\033[0m Output lógico incorrecto (salida contiene \"$output\" pero se esperaba \"$expected_output\")"
        ((fail++))
    elif [ $exit_code -ge 128 ]; then
        echo -e "\033[31mFAIL:\033[0m Crash detectado (exit code $exit_code)"
        echo "Salida:"
        cat "$TMP"
        ((fail++))
    else
        echo -e "\033[31mFAIL:\033[0m Salida inesperada"
        echo "Exit code: $exit_code"
        echo "Salida:"
        cat "$TMP"
        ((fail++))
    fi
done

echo -e "\n\033[1;34mTest de clasificación de PATHs\033[0m"

declare -A path_tests=(
    ["/usr/bin/python3"]="PATH"
    ["./myscript.sh"]="PATH"
    ["../folder/file"]="PATH"
    ["dir/folder/file"]="PATH"
    ["echo"]="COMMAND"
)

for input in "${!path_tests[@]}"; do
    expected_type=${path_tests[$input]}

    echo -e "\n\033[1;34mProbando input:\033[0m '$input' (esperado: $expected_type)"

    echo "$input" | $BIN > "$TMP" 2>&1
    output=$(<"$TMP")

    if echo "$output" | grep -q "Token: $input" && echo "$output" | grep -q "Type: $expected_type"; then
        echo -e "\033[32mPASS:\033[0m '$input' detectado correctamente como $expected_type"
        ((pass++))
    else
        echo -e "\033[31mFAIL:\033[0m '$input' mal clasificado"
        echo "Salida:"
        cat "$TMP"
        ((fail++))
    fi
done

echo -e "\n\033[1;34mTest de clasificación de otros tipos\033[0m"

declare -A misc_tests=(
    ["-l"]="OPTION"
    ["VAR=value"]="SETTING"
    ["<"]="RED_IN"
    [">"]="RED_OUT"
    ["<<"]="HEREDOC"
    [">>"]="APPEND_OUT"
    ["|"]="ERROR"
)

for input in "${!misc_tests[@]}"; do
    expected_type=${misc_tests[$input]}

    echo -e "\n\033[1;34mProbando input:\033[0m '$input' (esperado: $expected_type)"

    echo "$input" | $BIN > "$TMP" 2>&1
    output=$(<"$TMP")

    if echo "$output" | grep -q "Token: $input" && echo "$output" | grep -q "Type: $expected_type"; then
        echo -e "\033[32mPASS:\033[0m '$input' detectado correctamente como $expected_type"
        ((pass++))
    else
        echo -e "\033[31mFAIL:\033[0m '$input' mal clasificado"
        echo "Salida:"
        cat "$TMP"
        ((fail++))
    fi
done

echo -e "\n\033[1mResumen final:\033[0m"
echo -e "\033[32mPASS:\033[0m $pass"
echo -e "\033[31mFAIL:\033[0m $fail"

if [ "$fail" -eq 0 ]; then
    echo -e "\n\033[1;32mTodos los tests pasaron con éxito\033[0m"
else
    echo -e "\n\033[1;31mAlgunos tests fallaron. Revisá la salida arriba.\033[0m"
fi

rm -f "$TMP"
