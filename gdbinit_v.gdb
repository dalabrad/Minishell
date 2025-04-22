# gdbinit_v.gdb - breakpoints y ejecución automática

# Puntos de ruptura
break main
break ft_minisplit
break count_splitted
break split2array
break check_args_fixed

# Ejecutar con entrada predefinida
run <<<'echo "Lola que ase" >> out.txt | ls -l | wc -l'