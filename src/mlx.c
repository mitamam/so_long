/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 05:58:43 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/10 07:43:39 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	create_new_window(t_data *data)
{
	int		sizex;
	int		sizey;
	size_t	tile_w;
	size_t	tile_h;

	initialize_mlx(data);
	mlx_get_screen_size(data->mlx, &sizex, &sizey);
	tile_w = sizex / data->x;
	tile_h = sizey / data->y;
	if (tile_w < tile_h)
		data->tilesize = tile_w;
	else
		data->tilesize = tile_h;
	if (data->tilesize < 64)
		data->tilesize = 32;
	else
		data->tilesize = (data->tilesize / 32) * 32;
	data->mlx_win = mlx_new_window(data->mlx, (data->tilesize * data->x),
			((data->tilesize * data->y) + 16), "so_long");
	if (data->mlx_win == NULL)
		display_map_error(MLX_ERROR, data);
	composite_and_enlarge_img(data);
}

void	initialize_mlx(t_data *data)
{
	data->mlx = mlx_init();
	load_image_from_xpm_file(data, &data->floor);
	load_image_from_xpm_file(data, &data->wall);
	load_image_from_xpm_file(data, &data->exit);
	load_image_from_xpm_file(data, &data->item);
	load_image_from_xpm_file(data, &data->player.front);
	load_image_from_xpm_file(data, &data->player.back);
	load_image_from_xpm_file(data, &data->player.right);
	load_image_from_xpm_file(data, &data->player.left);
}
