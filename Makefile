# Colors for output
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

# Configuration
NAME := push_swap
NAME_BONUS := checker
CC := cc
CFLAGS	:=  -g -Wextra -Wall -Werror -Wunreachable-code

# Directories
SRC_DIR := ./srcs
SRC_BONUS_DIR := ./srcs_bonus
OBJ_DIR := ./objs
OBJ_BONUS_DIR := ./objs_bonus
LIBFT_DIR := ./libft

# Libraries
LIBFT := $(LIBFT_DIR)/libft.a
LIBS := $(LIBFT)

# Mandatory sources
SRCS := $(SRC_DIR)/main.c \
		$(SRC_DIR)/ft_sort.c \
		$(SRC_DIR)/ft_lis.c \
		$(SRC_DIR)/ft_turk.c \
		$(SRC_DIR)/ft_turk_utils.c \
		$(SRC_DIR)/ft_sort_small.c \
		$(SRC_DIR)/ft_stack.c \
		$(SRC_DIR)/ft_utils.c \
		$(SRC_DIR)/ft_parse.c \
		$(SRC_DIR)/ft_parse_utils.c \
		$(SRC_DIR)/ft_operations.c \
		$(SRC_DIR)/ft_find_nodes.c \
		$(SRC_DIR)/ft_print.c \
		$(SRC_DIR)/ft_print_s.c \
		$(SRC_DIR)/ft_print_r.c \
		$(SRC_DIR)/ft_print_two.c \
		$(SRC_DIR)/ft_align_ra.c \
		$(SRC_DIR)/ft_binary_search.c \

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

SRCS_BONUS := $(SRC_BONUS_DIR)/ft_checker_bonus.c \
			  $(SRC_BONUS_DIR)/ft_checker_utils_bonus.c \
			  $(SRC_BONUS_DIR)/ft_sort_bonus.c \
			  $(SRC_BONUS_DIR)/ft_stack_bonus.c \
			  $(SRC_BONUS_DIR)/ft_parse_bonus.c \
			  $(SRC_BONUS_DIR)/ft_parse_utils_bonus.c \
			  $(SRC_BONUS_DIR)/ft_operations_bonus.c \
			  $(SRC_BONUS_DIR)/ft_utils_bonus.c

OBJS_BONUS := $(SRCS_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)

all: $(NAME)

# Mandatory part

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)Created objects directory$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "$(CYAN)Compiled: $(notdir $<)$(RESET)"

$(NAME): $(LIBFT) $(OBJS)
	@rm -f $(BONUS_MARK)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) build successfully!$(RESET)"

# Bonus part
$(OBJ_BONUS_DIR):
	@mkdir -p $(OBJ_BONUS_DIR)
	@echo "$(BLUE)Created bonus objects directory$(RESET)"

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c | $(OBJ_BONUS_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "$(MAGENTA)Compiled bonus: $(notdir $<)$(RESET)"

$(NAME_BONUS): $(LIBFT) $(OBJS_BONUS)
	@rm -f $(MANDATORY_MARK)
	@echo "$(YELLOW)Linking $(NAME_BONUS) (bonus)...$(RESET)"
	@$(CC) $(OBJS_BONUS) $(LIBS) $(HEADERS) -o $(NAME_BONUS)
	@echo "$(GREEN)$(NAME_BONUS) (bonus) built successfully!$(RESET)"

bonus: $(NAME_BONUS)
# Libraries
$(LIBFT):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) bonus
	@echo "$(GREEN)Libft built successfully!$(RESET)"

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_BONUS_DIR)
	@rm -f $(MANDATORY_MARK)
	@rm -f $(BONUS_MARK)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(RED)Clean completed!$(RESET)"

fclean: clean
	@echo "$(RED)Full clean...$(RESET)"
	@rm -rf $(NAME)
	@rm -rf $(NAME_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(RED)Full clean completed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus
