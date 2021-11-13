# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 20:17:33 by mmasuda           #+#    #+#              #
#    Updated: 2021/11/11 12:27:31 by mmasuda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := so_long

SRC_FILES := main.c
SRC_DIR := srcs/
SRCS := $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJS := $(SRCS:.c=.o)

INCLUDE := includes/
LIB := lib/

MLX_DIR := $(LIB)mlx_linux/
MLX := -L/usr/X11R6/lib -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

LIBFT_DIR := $(LIB)libft/
LIBFT := $(LIBFT_DIR)libft.a

GNL_DIR := $(LIB)get_next_line/
GNL_SRC_FILES := get_next_line.c get_next_line_utils.c
GNL_SRCS := $(addprefix $(GNL_DIR), $(GNL_SRC_FILES))
GNL_OBJS := $(GNL_SRCS:.c=.o)

CC := gcc
CFLAGS := -Wall -Wextra -Werror

RM := rm -f

all : $(NAME)

$(NAME) : $(OBJS) $(GNL_OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(MLX) $(LIBFT) -o $@ $^

.c.o :
	$(CC) $(CFLAGS) -I$(INCLUDE) -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -c $< -o $@

clean :
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	$(RM) $(OBJS) $(GNL_OBJS)

fclean : clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
