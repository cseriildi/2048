NAME = 2048

SRCS = main.c \
		logic.c \
		debug.c \
		init.c \
		logic_move.c \
		logic_merge.c \
		logic_helper.c \
		logic_gameover.c \
		cleanup.c \
		visual_update.c \
		visual_menu.c \
		visual_resize.c \
		visual_setup.c \

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SAN_FLAGS = -fsanitize=address,undefined,bounds

VAL_FLAGS = --leak-check=full \
			--show-leak-kinds=all \
			--suppressions=ncurses.supp 

NCURSES_FLAGS = -lncurses

OBJ_DIR = obj
DEPS_DIR = $(OBJ_DIR)/.deps

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
DEPS = $(addprefix $(DEPS_DIR)/, $(notdir $(SRCS:.c=.d)))

.PHONY: all
all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(DEPS_DIR):
	@mkdir -p $(DEPS_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR) $(DEPS_DIR)
	@printf "$(ITALIC)"
	$(CC) $(CFLAGS) -MMD -MP -MF $(DEPS_DIR)/$(notdir $(<:.c=.d)) -c $< -o $@
	@printf "$(RESET)"

$(NAME): $(OBJS)
	@printf "$(ITALIC)"
	@${MAKE} -C ./libft --no-print-directory
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ./libft/libft.a $(NCURSES_FLAGS)
	@echo "$(GREEN)Executable: ./$(NAME)$(RESET)"

-include $(DEPS)

.PHONY: clean
clean:
	@printf "$(ITALIC)"
	@${MAKE} -C ./libft --no-print-directory fclean
	rm -rf $(OBJ_DIR)
	@printf "$(RESET)"

.PHONY: fclean
fclean: clean
	@printf "$(ITALIC)"
	rm -rf $(NAME)
	@printf "$(RESET)"

.PHONY: re
re: fclean all

.PHONY: run
run: all
	@echo
	@./$(NAME) $(ARGS)

.PHONY: val
val: re
	@echo
	valgrind $(VAL_FLAGS) ./$(NAME) $(ARGS)

.PHONY: san
san: CFLAGS += $(SAN_FLAGS)
san: run

$(DEPS):
	@true

ITALIC=\033[3m
BOLD=\033[1m
RESET=\033[0m
GREEN=\033[32m
BLUE=\033[34m
