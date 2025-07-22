#!/bin/bash

MINISHELL=./minishell
TMP=out.tmp
pass=0
fail=0

# Export some variables in the parent shell
export TESTVAR1="hello"
export TESTVAR2="world"
export EMPTYVAR=""

# Battery of inline tests
inline_tests=(
    "echo \$TESTVAR1"
    "echo \$TESTVAR1 \$TESTVAR2"
    "echo \"\$TESTVAR1\""
    "echo \$NOTSET"
    "echo \$EMPTYVAR"
    "export MYVAR=value"
    "echo \$MYVAR"
)
expected_inline=(
    "hello"
    "hello world"
    "hello"
    ""
    ""
    ""
    "value"
)

echo -e "\n\033[1m[Pruebas en línea de expansión de variables]\033[0m"

for i in "${!inline_tests[@]}"; do
    input="${inline_tests[$i]}"
    expected="${expected_inline[$i]}"

    echo "$input" | $MINISHELL > "$TMP" 2>&1
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

# Script de input por archivo
INPUT_FILE=input.expansion.txt
OUTPUT_FILE=output.expansion.txt

cat > $INPUT_FILE <<EOF
export A=hola
export B=mundo
echo \$A \$B
echo "\$A \$B"
echo '\$A \$B'
echo \$C
export ABC
echo "Val:\$A-End"
exit
EOF

echo -e "\n\033[1m[Pruebas por archivo de entrada]\033[0m"
$MINISHELL < $INPUT_FILE > $OUTPUT_FILE

cat <<EOF

======== SALIDA DE ARCHIVO ========
$(cat $OUTPUT_FILE)
===================================

EOF

# Resultados finales
echo -e "\033[1mResumen Final:\033[0m"
echo -e "\033[32mPASS:\033[0m $pass"
echo -e "\033[31mFAIL:\033[0m $fail"

rm -f "$TMP" "$INPUT_FILE"
