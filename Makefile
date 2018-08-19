# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/05 16:59:41 by sblauens          #+#    #+#              #
#    Updated: 2018/08/19 02:42:26 by sblauens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC_DIR = src

OBJ_DIR = obj

INC_DIR = include

LIB_DIR = .

SRC_FILES = ft_ls.c files.c list.c collect.c print.c \
			options.c cmp.c delete.c errors.c utils.c \
			longlist_modes.c longlist_sizes.c longlist_print.c \

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
	@$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@
	@echo "ft_ls: linking"
	@echo "ft_ls: ready to list !"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(LIB_NAMES) $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@echo "ft_ls: compiling $@"

$(OBJ_DIR):
	@mkdir $@

$(LIB_NAMES):
	@make -C $(addprefix $(LIB_DIR)/, $@)

clean: clean_lib clean_ft_ls

clean_ft_ls:
	@rm -rf $(OBJ)
	@rmdir $(OBJ_DIR) 2> /dev/null || true
	@echo "ft_ls: objects removed."

clean_lib:
	@make clean -C $(LIB_NAMES)

fclean: fclean_lib fclean_ft_ls

fclean_ft_ls: clean_ft_ls
	@rm -rf $(NAME)
	@echo "ft_ls: exec removed."

fclean_lib:
	@make fclean -C $(LIB_NAMES)

re: fclean all

.PHONY: all clean fclean re $(LIB_NAMES)
