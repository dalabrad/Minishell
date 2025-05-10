# ─────────────────────────────────────────────────────────────
# MAKEFILE
# ─────────────────────────────────────────────────────────────

NAME = minishell

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

AU_LIB = ./inc/array_utils.a
AU_SRCS = src/array_utils/array_utils.c
AU_OBJS = $(AU_SRCS:.c=.o)

MINISHELL_EXEC_LIB = ./inc/minishell_exec.a
EXEC_SRCS = $(wildcard src/cmd_execution/*.c) $(wildcard src/built-ins/*.c) $(wildcard src/environment/*.c) $(wildcard src/error_messages/*.c) $(wildcard src/minishell_data/*.c)
EXEC_OBJS = $(EXEC_SRCS:.c=.o)

MINISHELL_PARSING_LIB = ./inc/minishell_parsing.a
PARSING_SRCS = $(wildcard src/parsing/*.c) 
PARSING_OBJS = $(PARSING_SRCS:.c=.o)


MAIN = main.c
TEST_V = main_test_v.c
TEST_D = main_test_d.c

# ─────────────────────────────────────────────────────────────
# COMPILER
# ─────────────────────────────────────────────────────────────

CC = gcc
CFLAGS = -g3 -Iinc -Ilibft/inc -Wall -Werror -Wextra
LDFLAGS = -lreadline -lncurses

# ─────────────────────────────────────────────────────────────
# MAKE ALL DEFAULT TARGET
# ─────────────────────────────────────────────────────────────

all: $(NAME)

# ─────────────────────────────────────────────────────────────
# BUILD EXEC
# ─────────────────────────────────────────────────────────────

$(NAME): $(LIBFT) $(AU_LIB) $(MINISHELL_EXEC_LIB) $(MINISHELL_PARSING_LIB) $(MAIN)
	@echo "$(YELLOW)Compiling ./minishell executable...$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME) $(MAIN) $(MINISHELL_EXEC_LIB) $(MINISHELL_PARSING_LIB) $(AU_LIB) $(LIBFT) $(LDFLAGS)
	@echo "$(GREEN)./minishell executable created successfully.$(RESET)"

# ─────────────────────────────────────────────────────────────
# TEST: V- VLORENZO & D- DALABRAD
# ─────────────────────────────────────────────────────────────

testv: clean all $(LIBFT)
	@echo "$(YELLOW)Compiling Vanesa's ./minishell test executable...$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME) $(TEST_V) $(SRC) $(LIBFT) $(LDFLAGS)
	@echo "$(GREEN)Vanesa's ./minishell test executable created successfully.$(RESET)"

testd: $(LIBFT) $(MINISHELL_EXEC_LIB) $(MINISHELL_PARSING_LIB) $(AU_LIB)
	@echo "$(YELLOW)Compiling David's ./minishell test executable...$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME) $(TEST_D) $(MINISHELL_EXEC_LIB) $(MINISHELL_PARSING_LIB) $(AU_LIB) $(LIBFT) $(LDFLAGS)
	@echo "$(GREEN)David's ./minishell test executable created successfully.$(RESET)"

# ─────────────────────────────────────────────────────────────
# GDB DEBUGGING
# ─────────────────────────────────────────────────────────────

debugv: CFLAGS += -DDEBUG
debugv: testv
	@echo "$(BLUE)Binary compiled for GDB debugging (Vanesa's test).$(RESET)"

# ─────────────────────────────────────────────────────────────
# GDB TESTING
# ─────────────────────────────────────────────────────────────

gdb: clean all debugv
	@echo "$(BLUE)Lanzando GDB con ./minishell...$(RESET)"
	@if [ -f gdbinit_v.gdb ]; then \
		echo "$(YELLOW)Cargando script de breakpoints: gdbinit_v.gdb$(RESET)"; \
		gdb -x gdbinit_v.gdb ./minishell; \
	else \
		gdb ./minishell; \
	fi

# ─────────────────────────────────────────────────────────────
# CLEAN
# ─────────────────────────────────────────────────────────────

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(AU_LIB): $(AU_OBJS)
	@echo "$(YELLOW)Compiling array_utis.a library...$(RESET)"
	@ar rcs $(AU_LIB) $(AU_OBJS)
	@echo "$(GREEN)array_utils.a created successfully.$(RESET)"	

$(MINISHELL_PARSING_LIB): $(PARSING_OBJS)
	@echo "$(YELLOW)Compiling minishell_parsing.a library...$(RESET)"
	@ar rcs $(MINISHELL_PARSING_LIB) $(PARSING_OBJS)
	@echo "$(GREEN)minishell_parsing.a created successfully.$(RESET)"

$(MINISHELL_EXEC_LIB): $(EXEC_OBJS)
	@echo "$(YELLOW)Compiling minishell_exec.a library...$(RESET)"
	@ar rcs $(MINISHELL_EXEC_LIB) $(EXEC_OBJS)
	@echo "$(GREEN)minishell_exec.a created successfully.$(RESET)"

clean:
	@echo "$(YELLOW)Deleting all the object files...$(RESET)"
	@$(RM) $(EXEC_OBJS) $(PARSING_OBJS) $(AU_OBJS)
	@make -C $(LIBFT_DIR) clean
	@echo "$(GREEN)All the object files deleted successfully.$(RESET)"

fclean: clean
	@echo "$(YELLOW)Deleting the object files, *.a and executable file...$(RESET)"
	@$(RM) $(MINISHELL_EXEC_LIB) $(MINISHELL_PARSING_LIB) $(AU_LIB) $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)Everything deleted successfully.$(RESET)"

re: fclean all

# ─────────────────────────────────────────────────────────────
# VALGRIND TESTING
# ─────────────────────────────────────────────────────────────

VALGRIND_FLAGS = -s --leak-check=full --show-leak-kinds=all --track-fds=yes

valgrind: all
	@echo "$(BLUE)Ejecutando Valgrind con ./minishell...$(RESET)"
	valgrind $(VALGRIND_FLAGS) ./minishell

.PHONY: all clean fclean re testv testd debugv gdbv valgrind
