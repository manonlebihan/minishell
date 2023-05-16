# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 16:02:36 by mle-biha          #+#    #+#              #
#    Updated: 2023/01/27 15:42:10 by mle-biha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# --------------------------- Constant --------------------------- #

MAKEFLAGS		= --silent
NAME			= libft.a
CC				= gcc
CFLAGS			=-Wall -Wextra -Werror -I.
AR				= ar
ARFLAGS			= -cq

# --------------------------- Sources --------------------------- #

GNL_DIR		= gnl
LIB_DIR		= libft
PRINTF_DIR	= ft_printf
	
GNL_SRC		= 	get_next_line.c \
					get_next_line_utils.c \
					get_next_line_bonus.c \
					get_next_line_utils_bonus.c \

LIB_SRC		= 	ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_lstadd_back_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstmap_bonus.c \
				ft_lstnew_bonus.c \
				ft_lstsize_bonus.c \

PRINTF_SRC	= ft_check_arg_type.c \
				ft_printf.c \
				ft_putchar.c \
				ft_puthexa.c \
				ft_putnbr.c \
				ft_putpointer.c \
				ft_putstr.c \
				ft_putunsigned.c \

SRC_GNL		= $(addprefix $(GNL_DIR)/, $(GNL_SRC))
SRC_LIB		= $(addprefix $(LIB_DIR)/, $(LIB_SRC))
SRC_PRINTF	= $(addprefix $(PRINTF_DIR)/, $(PRINTF_SRC))

OBJ_GNL		= $(SRC_GNL:.c=.o)
OBJ_LIB		= $(SRC_LIB:.c=.o)
OBJ_PRINTF	= $(SRC_PRINTF:.c=.o)

OBJS		= $(OBJ_GNL) $(OBJ_LIB) $(OBJ_PRINTF)

# --------------------------- Rules --------------------------- #

all: $(NAME)

%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : clean fclean re
