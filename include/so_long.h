/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 22:34:59 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/09 09:49:36 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
#include <X11/Xlib.h>
# include <mlx.h>
# include <libft.h>
# include <get_next_line.h>
# include <structures.h>

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_EXPOSE 12
# define X_EVENT_RED_CROSS 17
# define BUFFER_SIZE 256
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

// dfs.c
char	*ft_strjoinjoin(char const *s1, char const *s2, char const *s3);
void	*ft_memset_with_malloc(int c, size_t n);
void	initialize_dfs_map(t_data *data);
void	dfs(char **dfs_map, size_t x, size_t y, int *check);
void	check_with_dfs_if_map_is_closed(t_data *data);

// draw.c
void composite_and_enlarge_img(t_data *data);
void	count_number_of_digits(int *digits, size_t n);
char	*ft_itoa_size_t(size_t n);
void	display_number_of_steps(t_data *data);
void	draw_tile(t_img *img, size_t x, size_t y, t_data *data);
void	draw_map_on_window(t_data *data);

// error.c
void	display_error(t_data *data);
void	display_map_error(const t_errors error, t_data *data);
int		check_rectangular_and_invalid_char(t_data *data);
t_bool	is_file_extension_incorrect(t_data *data);
void	check_error_on_map(t_data *data);

// free.c
void	destroy_and_free_img(t_data *data, t_img *img);
void	free_all_img(t_data *data);
void	exit_game(t_data *data, int ret);

// image.c
double	ft_floor(double x);
void	enlarge_img(t_img *img, size_t tilesize, t_data *data);
void	composite_img(t_img *img, t_img *bg);
void	load_image_from_xpm_file(t_data *data, t_img *img);
t_img	initialize_img(t_data *data, char *img_name);

// init.c
void	count_object(char *buf, t_data *data);
void	initialize_data(t_data *data, char *filename);

// map.c
void	change_player_img_match_direction(t_player *player, t_data *data);
t_bool	is_new_position_off_map_or_wall(int dx, int dy, t_data *data);
void	save_map_with_gnl(t_data *data);
void	parse_map_from_file(t_data *data);

// mlx.c
int		close_window(t_data *data);
int		game_loop(t_data *data);
void	create_new_window(t_data *data);
void	initialize_mlx(t_data *data);

// move.c
void	move(t_move move, int dx, int dy, t_data *data);
int		pressed_key(int key_code, t_data *data);

#endif
