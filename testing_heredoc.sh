#!/bin/bash

# Requiere que ./minishell esté compilado y accesible

MINISHELL=./minishell
TMP_OUTPUT="out_heredoc.txt"

run_heredoc_test() {
echo "[TEST] Heredoc simple → 'cat << EOF'"
$MINISHELL > "$TMP_OUTPUT" << EOF
cat << EOF
hola
EOF
EOF

if grep -q "hola" "$TMP_OUTPUT"; then
    echo "[OK] heredoc simple contiene 'hola'"
else
    echo "[FAIL] heredoc simple"
    echo "Expected: 'hola'"
    echo "Got:"
    cat "$TMP_OUTPUT"
fi
}

run_heredoc_multiline() {
echo "[TEST] Heredoc multiline → 'cat << END'"
$MINISHELL > "$TMP_OUTPUT" << EOF
cat << END
uno
dos
tres
END
EOF

if grep -q "dos" "$TMP_OUTPUT" && grep -q "tres" "$TMP_OUTPUT"; then
    echo "[OK] heredoc multilinea"
else
    echo "[FAIL] heredoc multilinea"
    echo "Expected: lines 'uno', 'dos', 'tres'"
    echo "Got:"
    cat "$TMP_OUTPUT"
fi
}

# Ejecutar tests
run_heredoc_test
run_heredoc_multiline

# Limpiar
rm -f "$TMP_OUTPUT" /tmp/1
