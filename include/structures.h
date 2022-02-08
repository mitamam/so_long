/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 07:10:28 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/07 05:54:41 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

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
	void			*img_ptr;
	char			*path;
	unsigned int	*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
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
	char			**dfs_map;
	coord			x;
	coord			y;
	t_bool			pressed_flag;
	size_t			string_y;
	size_t			tilesize;
	size_t			steps;
	int				steps_digits;
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
