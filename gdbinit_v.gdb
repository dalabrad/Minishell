# gdbinit_v.gdb - breakpoints y ejecución automática

# Puntos de ruptura
break main
break check_args_fixed

# Ejecutar con entrada predefinida
run <<< 'echo "hola que ase" > out.txt | ls -l | wc -l'