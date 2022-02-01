/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 22:34:59 by mmasuda           #+#    #+#             */
/*   Updated: 2022/01/31 20:55:58 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h> // prinf
# include <unistd.h> // read
# include <stdlib.h> // exit, malloc
# include <string.h> // strerror
# include <errno.h> // errno
# include <fcntl.h> // open

# include <mlx.h>
# include <libft.h>
# include <get_next_line.h>

# define BUFFER_SIZE 256
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

typedef size_t coord;

typedef enum e_bool { false, true } t_bool;

typedef enum e_move
{
	UP,
	LEFT,
	DOWN,
	RIGHT,
}			t_move;

typedef enum e_errors
{
	INCORRECT_ARG,
	INCORRECT_EXT,
	NOT_RECTANGULAR,
	NOT_ENCLOSED,
	NO_EXIT,
	NO_START_POSITION,
	NO_COLLECTIBLES,
	MULTIPLE_START_POSITION,
	INVALID_CHARACTER,
	MALLOC_ERROR,
	MLX_ERROR,
	UNKNOWN_ERROR,
	INVALID,
}			t_errors;

typedef struct s_img
{
	void	*img;
	char	*path;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct	s_player
{
	size_t x;
	size_t y;
	enum e_move move;
	struct s_img front;
	struct s_img back;
	struct s_img right;
	struct s_img left;
}				t_player;

typedef struct s_data
{
	char			*filename;
	void			*mlx;
	void			*mlx_win;
	char			**map;
	coord			x;
	coord			y;
	t_bool			pressed_flag;
	size_t			tilesize;
	size_t			steps;
	size_t			collectibles;
	size_t			exits;
	size_t			start_position;
	struct s_player	player;
	struct s_img	floor;
	struct s_img	wall;
	struct s_img	exit;
	struct s_img	item;
}				t_data;

#endif
