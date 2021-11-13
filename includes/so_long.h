/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:18:08 by mmasuda           #+#    #+#             */
/*   Updated: 2021/11/11 12:04:02 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include <mlx.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <libft.h>
#include <get_next_line.h>

# define TILE_SIZE 16
# define BUFFER_SIZE 256

typedef enum e_bool { false, true } t_bool;

typedef enum e_errors
{
	INCORRECT_ARG,
	INCORRECT_EXT,
	OPEN_ERROR,
	NOT_RECTANGLE,
	NOT_ENCLOSED,
	NOT_EXIST_EXIT,
	NOT_EXIST_PLAYER_POS,
	NOT_EXIST_COLLECTIBLE,
	DUPLICATE_PLAYER_POS,
	INVALID_CHARACTER,
	MALLOC_ERROR,
	INVALID,
}			t_errors;

typedef struct s_map
{
	int fd;
	char *filename;
	char **map;
	long x;
	long y;
	long collectibles;
}				t_map;

typedef struct s_dfs
{
	char **dfs_map;
	char now;
	char up;
	char down;
	char left;
	char right;
}				t_dfs;

typedef struct s_player
{
	void *player_img;
	long first_pos_x;
	long first_pos_y;
}				t_player;


typedef struct	s_mlx
{
	void *mlx_ptr;
	void *win_ptr;
	long win_width;
	long win_height;
	struct s_map map;
	struct s_dfs dfs;
	struct s_player player;
}				t_mlx;

#endif