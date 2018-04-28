# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/05 16:59:41 by sblauens          #+#    #+#              #
#    Updated: 2018/04/28 16:01:33 by sblauens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC_DIR = src

OBJ_DIR = obj

INC_DIR = include

LIB_DIR = lib

SRC_FILES = ft_ls.c read.c print.c delete.c

LIB_NAMES = libft

CC = clang

CFLAGS = -Wall -Wextra -Werror

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

LIB = $(addprefix $(LIB_DIR)/, $(LIB_NAMES))

CPPFLAGS = -I $(INC_DIR) $(addprefix -I , $(LIB))

LDFLAGS = $(addprefix -L , $(LIB))

LDLIBS = $(addprefix -, $(patsubst lib%, l%, $(LIB_NAMES)))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(LIB_NAMES) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir $@

$(LIB_NAMES):
	@make -C $(addprefix $(LIB_DIR)/, $@)

clean:
	rm -rf $(OBJ)
	@rmdir $(OBJ_DIR) 2> /dev/null || true

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
