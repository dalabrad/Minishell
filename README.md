✅ Exit Command Fix and Memory Management

    The condition if (ft_strcmp(line[0], "exit")) was corrected to if (ft_strcmp(line[0], "exit") == 0) to properly detect the exit command.

    Double free was avoided by freeing line only once after command processing.

    The memory cleanup logic was centralized: line is now freed either inside cleanup() or after process_input_line(), not both.
✅ Result:

    Valgrind now reports:

definitely lost: 0 bytes
indirectly lost: (yes but from readline)
no invalid free() or uninitialized value errors

Exit works as expected and prints exit before terminating the shell.

Main loop and signal handlers remain clean and stable.