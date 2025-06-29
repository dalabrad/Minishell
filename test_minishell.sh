#!/bin/bash

# Test script for final Minishell version

MINISHELL_EXEC=./minishell
TEST_LOG="minishell_test.log"
EXPECTED="expected_output.txt"
RESULT="result_output.txt"
EXIT_CODE=0

echo "Running Minishell tests..." > $TEST_LOG

run_test() {
    TEST_DESC="$1"
    INPUT_CMD="$2"
    EXPECTED_OUT="$3"

    echo -n "$TEST_DESC: " >> $TEST_LOG
    echo "$INPUT_CMD" | $MINISHELL_EXEC > $RESULT 2>&1
    echo -n "$EXPECTED_OUT" > $EXPECTED

    if diff -q $EXPECTED $RESULT > /dev/null; then
        echo "✅ Passed" >> $TEST_LOG
    else
        echo "❌ Failed" >> $TEST_LOG
        echo "Expected: [$EXPECTED_OUT]" >> $TEST_LOG
        echo "Got:      [$(cat $RESULT)]" >> $TEST_LOG
        EXIT_CODE=1
    fi
}

# === BUILTIN COMMANDS ===
run_test "Built-in: echo" "echo Hello World" "Hello World"
run_test "Built-in: pwd" "pwd" "$(pwd)"
run_test "Built-in: env" "env" "$(env)"
run_test "Built-in: export+env" "export TEST_VAR=abc && env | grep TEST_VAR" "TEST_VAR=abc"
run_test "Built-in: unset" "export RM_ME=bye && unset RM_ME && env | grep RM_ME" ""

# === VARIABLE EXPANSION ===
run_test "Expansion: simple" "export X=42 && echo $X" "42"
run_test "Expansion: exit status" "false; echo $?" "1"

# === REDIRECTIONS ===
run_test "Redirection out" "echo Hello > test_output.txt && cat test_output.txt" "Hello"
run_test "Redirection append" "echo Line1 > file && echo Line2 >> file && cat file" "Line1
Line2"
run_test "Redirection in" "echo input > input.txt && cat < input.txt" "input"

# === SYNTAX ERRORS ===
run_test "Syntax: invalid redir" "echo hola >|" "minishell: syntax error near unexpected token `|'"

# === NON-BUILTIN COMMAND ===
run_test "Non-builtin: ls" "ls | grep minishell" "$(ls | grep minishell)"

# Clean up
rm -f test_output.txt file input.txt $EXPECTED $RESULT

exit $EXIT_CODE
