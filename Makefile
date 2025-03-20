NAME = minishell

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MINISHELL_EXEC_LIB = ./inc/minishell_exec.a
MINISHELL_PARSING_LIB = ./inc/minishell_parsing.a

SRCS = $(wildcard src/*.c)

MAIN = main.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft/inc -Iinc
RM = rm -f

GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[1;33m
RESET = \033[0m


$(NAME): $(LIBFT) $(MINISHELL_EXEC_LIB) $(MINISHELL_PARSING_LIB) $(MAIN)
	@echo "$(YELLOW)Compiling ./minishell executable...$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME) $(MAIN) $(MINISHELL_EXEC_LIB) $(MINISHELL_PARSING_LIB) $(LIBFT)
	@echo "$(GREEN)./mishell executable created successfully.$(RESET)"

$(LIBFT): 
	@make -C $(LIBFT_DIR)

$(MINISHELL_EXEC_LIB): $(OBJS)
	@echo "$(YELLOW)Compiling minishell_exec.a library...$(RESET)"
	@ar rcs $(MINISHELL_EXEC_LIB) $(OBJS)
	@echo "$(GREEN)minishell_exec.a created successfully.$(RESET)"

$(MINISHELL_PARSING_LIB): $(OBJS)
	@echo "$(YELLOW)Compiling minishell_parsing.a library...$(RESET)"
	@ar rcs $(MINISHELL_PARSING_LIB) $(OBJS)
	@echo "$(GREEN)minishell_parsing.a created successfully.$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@


all: $(NAME)

clean:
	@echo "$(YELLOW)Deleting all the object files...$(RESET)"
	@$(RM) $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@echo "$(GREEN)All the object files deleted succesfully.$(RESET)"

fclean: clean
	@echo "$(YELLOW)Deleting the object files, *.a and executable file...$(RESET)"
	@$(RM) $(MINISHELL_EXEC_LIB) $(MINISHELL_PARSING_LIB) $(NAME) 
	@make -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)Everything deleted succesfully.$(RESET)"

re: fclean all

.PHONY: all clean fclean re