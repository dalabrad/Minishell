HOTFIX EXPANSION

| TEST                 | RESULT                 | SCORE                  |
| -------------------- | ---------------------- | ---------------------- |
| `echo $A $B`         | `hola mundo`           | ✅                     |
| `echo "$A $B"`       | `hola mundo`           | ✅                     |
| `echo '$A $B'`       | `$A $B` (sin expandir) | ❌ **(ver más abajo)** |
| `echo $C`            | *(línea vacía)*        | ✅                     |
| `export ABC` sin `=` | no modifica `envp`     | ✅                     |
| `echo "Val:$A-End"`  | `Val:hola-End`         | ✅                     |
