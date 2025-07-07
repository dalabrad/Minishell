#!/bin/bash

MINISHELL=./minishell
USE_VALGRIND=${USE_VALGRIND:-false}

run_test() {
	local name="$1"
	local input="$2"
	local expected="$3"

	if [ "$USE_VALGRIND" = true ]; then
		output=$(echo -e "$input" | valgrind --leak-check=full "$MINISHELL" 2>/dev/null)
	else
		output=$(echo -e "$input" | "$MINISHELL")
	fi

	echo "$output" | grep -q "$expected"
	if [ $? -eq 0 ]; then
		echo "[OK] $name"
	else
		echo "[FAIL] $name"
		echo "Expected: $expected"
		echo "Got:"
		echo "$output"
	fi
}

### TESTS DE EXPORT SIMPLES
run_test "export simple sin valor" \
	"export TESTVAR1\nexport\nexit" \
	"declare -x TESTVAR1"

run_test "export con valor vacío" \
	"export TESTVAR2=\nexport\nexit" \
	"declare -x TESTVAR2=\"\""

run_test "export con valor definido" \
	"export TESTVAR3=hola\nexport\nexit" \
	"declare -x TESTVAR3=\"hola\""

run_test "export var=valor aparece en env" \
	"export TESTVAR4=valor\nenv\nexit" \
	"TESTVAR4=valor"

run_test "export sin valor NO aparece en env" \
	"export TESTVAR5\nenv\nexit" \
	"TESTVAR5" # Este debería fallar si aparece (porque no debe estar)

run_test "export var con espacios (entre comillas)" \
	"export VAR6=\"hello world\"\nexport\nexit" \
	"declare -x VAR6=\"hello world\""

run_test "export overwrite (sobrescribe valor)" \
	"export TESTVAR7=uno\nexport TESTVAR7=dos\nexport\nexit" \
	"declare -x TESTVAR7=\"dos\""

run_test "expansión de \$TESTVAR3" \
	"export TESTVAR3=hola\necho \$TESTVAR3\nexit" \
	"hola"

run_test "expansión de \$? después de export" \
	"export TESTVAR8=ok\necho \$?\nexit" \
	"0"

run_test "export inválido no crash (solo nombre =)" \
	"export =\nexit" \
	"minishell"
