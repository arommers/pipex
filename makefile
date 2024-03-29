# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: arommers <arommers@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/03/29 11:13:20 by arommers      #+#    #+#                  #
#    Updated: 2023/04/28 10:42:36 by arommers      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex

LIBFT = ./libft/libft.a
INCLUDE = -I./include
SRC =	./src/main.c ./src/utilities.c	\
		./src/children.c ./src/error.c	\
		./src/split_quote.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

BLACK   := \033[30m
RED     := \033[31m
GREEN   := \033[32m
YELLOW  := \033[33m
BLUE 	:= \033[96m
MAGENTA := \033[38;5;206m
CYAN    := \033[36m
WHITE   := \033[37m
RESET   := \033[0m
BOLD    := \033[1m
DIM     := \033[2m
ITALIC  := \033[3m
UNDER   := \033[4m
BLINK   := \033[5m
REVERSE := \033[7m
HIDDEN  := \033[8m
PINK 	:= \033[35m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) 
	@echo "Compiled with $(GREEN)$(BOLD)$(CFLAGS)$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "$(RED)$(BOLD)----------------------------------------"
	@echo "     $(NAME) = NOW READY FOR USE!"
	@echo "----------------------------------------$(RESET)"

$(LIBFT):
	@$(MAKE) -C ./libft


$(OBJ_DIR)/%.o: ./src/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiled ✅ $(RED) $(BOLD) $^ $(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

clean:
	@$(MAKE) clean -C ./libft
	@rm -rf $(OBJ_DIR)
	@rm -rf $(BONUS_DIR)

fclean: clean
	@$(MAKE) fclean -C ./libft
	@rm -f $(NAME)
	@rm -f $(BONUS)
	@echo "$(BLUE) $(BOLD)$(NAME) $(RESET) Cleansed ✅"

re: fclean all

.PHONY: all clean fclean re bonus