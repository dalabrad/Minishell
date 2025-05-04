#!/bin/bash

BIN=./minishell
TMP=out.tmp
pass=0
fail=0

# Export some variables in the shell environment (for your real shell)
export TESTVAR1="hello"
export TESTVAR2="world"
export EMPTYVAR=""

tests=(
    "echo \$TESTVAR1"
    "echo \$TESTVAR1 \$TESTVAR2"
    "echo \"\$TESTVAR1\""
    "echo \$NOTSET"
    "echo \$EMPTYVAR"
    "export MYVAR=value"
    "echo \$MYVAR"
)

expected_outputs=(
    "hello"
    "hello world"
    "hello"
    ""
    ""
    ""
    "value"
)

echo -e "\n\033[1mIniciando pruebas de expansión de variables\033[0m"

for i in "${!tests[@]}"; do
    input="${tests[$i]}"
    expected="${expected_outputs[$i]}"

    echo "$input" | $BIN > "$TMP" 2>&1
    output=$(<"$TMP")

    echo -e "\nTest $((i + 1)): \033[1m$input\033[0m"
    if [[ "$output" == *"$expected"* ]]; then
        echo -e "\033[32mPASS\033[0m: Contiene \"$expected\""
        ((pass++))
    else
        echo -e "\033[31mFAIL\033[0m: Esperado \"$expected\" pero se obtuvo:"
        echo "$output"
        ((fail++))
    fi
done

echo -e "\n\033[1mResumen Final:\033[0m"
echo -e "\033[32mPASS:\033[0m $pass"
echo -e "\033[31mFAIL:\033[0m $fail"

rm -f "$TMP"

