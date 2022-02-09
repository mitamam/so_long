/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 05:58:43 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/09 14:17:30 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int	close_window(t_data *data)
{
	exit_game(data, 0);
	return (0);
}

int	game_loop(t_data *data)
{
	if (data->pressed_flag == true)
	{
		change_player_img_match_direction(&data->player, data);
		display_number_of_steps(data);
		if (data->map[data->player.y][data->player.x] == 'C')
		{
			data->collectibles--;
			printf("collectibles: %ld\n", data->collectibles);
			data->map[data->player.y][data->player.x] = '0';
		}
		else if (data->map[data->player.y][data->player.x] == 'E')
		{
			if (data->collectibles == 0)
				exit_game(data, 0);
			else
				printf("\x1b[31myou haven't got all the collectibles!\x1b[39m\n");
		}
	}
	data->pressed_flag = false;
	return (0);
}

void	create_new_window(t_data *data)
{
	int	sizex;
	int	sizey;
	size_t	tile_w;
	size_t	tile_h;

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
	data->mlx_win = mlx_new_window(data->mlx, (data->tilesize * data->x), ((data->tilesize * data->y) + 16), "so_long");
	if (data->mlx_win == NULL)
		display_map_error(MLX_ERROR, data);
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
