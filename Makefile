# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 14:30:36 by mle-biha          #+#    #+#              #
#    Updated: 2023/05/16 18:22:02 by mle-biha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --------------------------- Constant --------------------------- #

CC					= gcc
CFLAGS				= -Wall -Wextra -Werror -I. -g -ggdb
NAME				= minishell
INCLUDES			= -I $(DIR_LIBFT) -I $(INC_DIR) -I $(DIR_LIBFT)/ft_printf -I \
							$(DIR_LIBFT)/gnl -I $(DIR_LIBFT)/libft
LIBS				= -L $(DIR_LIBFT) -lft -lreadline
# NAME_BONUS		= minishell_bonus

# --------------------------- Sources --------------------------- #

# Directories
SRC_DIR				= srcs
OBJ_DIR				= objs
INC_DIR				= includes

# Files	
DIR_LIBFT			= Libft
LIBFT				= Libft/libft.a

# Sources and objects
SRC					= $(SRC_DIR)/main.c \
						$(SRC_DIR)/builtin_cd.c \
						$(SRC_DIR)/builtin_echo.c \
						$(SRC_DIR)/builtin_env.c \
						$(SRC_DIR)/builtin_exit.c \
						$(SRC_DIR)/builtin_pwd.c \
						$(SRC_DIR)/builtin.c \
						$(SRC_DIR)/env.c \
						$(SRC_DIR)/extern.c \
						$(SRC_DIR)/free.c \
						$(SRC_DIR)/minishell.c \
						$(SRC_DIR)/parser.c \
						$(SRC_DIR)/print.c \
						$(SRC_DIR)/tokenizer.c \
						$(SRC_DIR)/tree.c 
OBJ					= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# --------------------------- Colors --------------------------- #

GREEN				= \e[1;32m
YELLOW				= \e[1;33m
BLUE				= \e[1;34m
MAGENTA				= \e[1;35m
NO_COLOR			= \e[0m

# --------------------------- Rules --------------------------- #

all: $(NAME) $(LIBFT)

$(LIBFT):
	@echo "\n$(MAGENTA)Creating Libft...$(NO_COLOR)"
	@make -C $(DIR_LIBFT) --no-print-directory
	@echo "$(GREEN)Libft OK !$(NO_COLOR)\n"
	
$(NAME): $(OBJ) $(LIBFT)
	@echo "$(MAGENTA)Creating minishell...$(NO_COLOR)"	
	@$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(LIBS) -o $(NAME)
	@echo "$(GREEN)minishell OK !$(NO_COLOR)\n"

$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(INCLUDES) -o $@ -c $< $(CFLAGS) 

clean:
	@echo "\n$(YELLOW)Cleaning objects !$(NO_COLOR)"
	@rm -f $(OBJ)
	@make -C $(DIR_LIBFT) --no-print-directory clean
	@echo "$(GREEN)Objects cleaned !$(NO_COLOR)\n"
	
fclean: clean
	@echo "$(YELLOW)Cleaning everything !$(NO_COLOR)"
	@rm -f $(NAME)
	@make -C $(DIR_LIBFT) --no-print-directory fclean
	@echo "$(GREEN)Everything cleaned !$(NO_COLOR)\n"

re: fclean all

.PHONY : clean fclean re