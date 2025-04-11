# ─────────────────────────────────────────────────────────────
# MAKEFILE
# ─────────────────────────────────────────────────────────────

NAME = minishell

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MINISHELL_EXEC_LIB = ./inc/minishell_exec.a
MINISHELL_PARSING_LIB = ./inc/minishell_parsing.a

SRC := $(filter-out src/parsing/parser_test.c, $(wildcard src/parsing/*.c))
OBJS = $(SRC:.c=.o)

MAIN = main.c
TEST_V = main_test_v.c
TEST_D = main_test_d.c

# ─────────────────────────────────────────────────────────────
# COMPILER
# ─────────────────────────────────────────────────────────────

CC = gcc
CFLAGS = -g3 -Iinc -Ilibft/inc
LDFLAGS = -lreadline -lncurses

# ─────────────────────────────────────────────────────────────
# MAKE ALL DEFAULT TARGET
# ─────────────────────────────────────────────────────────────

all: $(NAME)

# ─────────────────────────────────────────────────────────────
# BUILD EXEC
# ─────────────────────────────────────────────────────────────

$(NAME): $(LIBFT) $(MINISHELL_EXEC_LIB) $(MINISHELL_PARSING_LIB) $(MAIN)
	@echo "$(YELLOW)Compiling ./minishell executable...$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME) $(MAIN) $(MINISHELL_EXEC_LIB) $(MINISHELL_PARSING_LIB) $(LIBFT) $(LDFLAGS)
	@echo "$(GREEN)./minishell executable created successfully.$(RESET)"

# ─────────────────────────────────────────────────────────────
# TEST: V- VLORENZO & D- DALABRAD
# ─────────────────────────────────────────────────────────────

testv: $(LIBFT)
	@echo "$(YELLOW)Compiling Vanesa's ./minishell test executable...$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME) $(TEST_V) $(SRC) $(LIBFT) $(LDFLAGS)
	@echo "$(GREEN)Vanesa's ./minishell test executable created successfully.$(RESET)"

testd: $(LIBFT) $(MINISHELL_EXEC_LIB) $(MINISHELL_PARSING_LIB)
	@echo "$(YELLOW)Compiling David's ./minishell test executable...$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME) $(TEST_D) $(MINISHELL_EXEC_LIB) $(MINISHELL_PARSING_LIB) $(LIBFT) $(LDFLAGS)
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

gdb: debugv
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

$(MINISHELL_PARSING_LIB): $(OBJS)
	@echo "$(YELLOW)Compiling minishell_parsing.a library...$(RESET)"
	@ar rcs $(MINISHELL_PARSING_LIB) $(OBJS)
	@echo "$(GREEN)minishell_parsing.a created successfully.$(RESET)"

$(MINISHELL_EXEC_LIB): $(OBJS)
	@echo "$(YELLOW)Compiling minishell_exec.a library...$(RESET)"
	@ar rcs $(MINISHELL_EXEC_LIB) $(OBJS)
	@echo "$(GREEN)minishell_exec.a created successfully.$(RESET)"

clean:
	@echo "$(YELLOW)Deleting all the object files...$(RESET)"
	@$(RM) $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@echo "$(GREEN)All the object files deleted successfully.$(RESET)"

fclean: clean
	@echo "$(YELLOW)Deleting the object files, *.a and executable file...$(RESET)"
	@$(RM) $(MINISHELL_EXEC_LIB) $(MINISHELL_PARSING_LIB) $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)Everything deleted successfully.$(RESET)"

re: fclean all

.PHONY: all clean fclean re testv testd debugv gdbv
