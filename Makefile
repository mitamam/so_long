# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 20:17:33 by mmasuda           #+#    #+#              #
#    Updated: 2022/01/31 17:19:13 by mmasuda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := so_long

SRC_FILE := main.c
SRC_DIR := src/
SRC = $(addprefix $(SRC_DIR), $(SRC_FILE))
INC := include/
CC := gcc
CFLAGS := -Wall -Wextra -Werror
MLX_DIR := mlx_Linux
LIB := -L$(MLX_DIR) -lmlx -I$(MLX_DIR) -L/usr/lib -lXext -lX11 -lm -lz 

LIBFT_DIR := libft/
LIBFT := $(LIBFT_DIR)libft.a

GNL_FILE := get_next_line.c get_next_line_utils.c
GNL_DIR := get_next_line/
GNL_SRC := $(addprefix $(GNL_DIR), $(GNL_FILE))

OBJ := $(SRC:.c=.o) $(GNL_SRC:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -I$(INC) -I/usr/include -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX_DIR) -o $@

$(NAME) : $(OBJ)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT) $(LIB)

clean :
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	$(RM) $(OBJ)

fclean : clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

mac : LIB += -L/usr/X11R6/lib
mac : re
	
debug: CFLAGS += -g3 -fsanitize=address
debug: re


mdebug : LIB += -L/usr/X11R6/lib
mdebug : CFLAGS += -g3 -fsanitize=address
mdebug : re

.PHONY: all clean fclean re
