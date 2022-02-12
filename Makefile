# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 20:17:33 by mmasuda           #+#    #+#              #
#    Updated: 2022/02/12 03:36:16 by mmasuda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := so_long
BONUS := so_long_bonus

SRC_FILE := main.c dfs.c draw.c error.c free.c image.c \
				init.c map.c mlx.c move.c hook.c utils.c
BONUS_SRC_FILE := main_bonus.c dfs_bonus.c draw_bonus.c error_bonus.c \
					free_bonus.c image_bonus.c init_bonus.c map_bonus.c \
					mlx_bonus.c move_bonus.c hook_bonus.c utils_bonus.c
SRC_DIR := src/
BONUS_SRC_DIR := bonus_src/
SRC := $(addprefix $(SRC_DIR), $(SRC_FILE))
BONUS_SRC := $(addprefix $(BONUS_SRC_DIR), $(BONUS_SRC_FILE))
INC := include/
CFLAGS := -Wall -Wextra -Werror
MLX_DIR := mlx_Linux
LIB := -L$(MLX_DIR) -lmlx -I$(MLX_DIR) -L/usr/lib -lXext -lX11 -lm -lz 

LIBFT_DIR := libft/
LIBFT := $(LIBFT_DIR)libft.a

GNL_FILE := get_next_line.c get_next_line_utils.c
GNL_DIR := get_next_line/
GNL_SRC := $(addprefix $(GNL_DIR), $(GNL_FILE))

OBJ := $(SRC:.c=.o) $(GNL_SRC:.c=.o)
BONUS_OBJ := $(BONUS_SRC:.c=.o) $(GNL_SRC:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -D BUFFER_SIZE=256 -c $< -I$(INC) -I/usr/include -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX_DIR) -o $@

$(NAME) : $(OBJ)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT) $(LIB)

clean :
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	$(RM) $(OBJ) $(BONUS_OBJ)

fclean : clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(NAME) $(BONUS)


re: fclean all
	
bonus : $(BONUS)

$(BONUS) : $(BONUS_OBJ)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT) $(LIB)

debug: CFLAGS += -g3 -fsanitize=address
debug: re

.PHONY: all clean fclean re bonus
