/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 06:00:23 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/10 07:49:07 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long_bonus.h>

void	display_number_of_steps(t_data *data)
{
	char	*steps;
	size_t	i;
	size_t	j;
	size_t	fill_width;

	i = 0;
	data->string_y = (data->tilesize * data->y) + 12;
	count_number_of_digits(&data->steps_digits, data->steps);
	fill_width = data->steps_digits * 6;
	steps = ft_itoa_size_t(data->steps);
	if (steps == NULL)
		return ;
	while (i < 20)
	{
		j = 0;
		while (j++ < fill_width)
			mlx_pixel_put(data->mlx, data->mlx_win, 38 + j,
				data->string_y - 10 + i, 0x0);
		i++;
	}
	mlx_string_put(data->mlx, data->mlx_win, 0, data->string_y,
		0xFFFFFF, "steps: ");
	mlx_string_put(data->mlx, data->mlx_win, 40, data->string_y + 1,
		0xFFFFFF, steps);
	free(steps);
}

void	draw_tile(t_img *img, size_t x, size_t y, t_data *data)
{
	size_t	put_x;
	size_t	put_y;

	put_x = data->tilesize * x;
	put_y = data->tilesize * y;
	mlx_put_image_to_window(data->mlx, data->mlx_win,
		img->img_ptr, put_x, put_y);
}

void	composite_and_enlarge_img(t_data *data)
{
	composite_img(&data->player.front, &data->floor);
	composite_img(&data->player.back, &data->floor);
	composite_img(&data->player.right, &data->floor);
	composite_img(&data->player.left, &data->floor);
	composite_img(&data->wall, &data->floor);
	composite_img(&data->exit, &data->floor);
	composite_img(&data->item, &data->floor);
	enlarge_img(&data->player.front, data->tilesize, data);
	enlarge_img(&data->player.back, data->tilesize, data);
	enlarge_img(&data->player.right, data->tilesize, data);
	enlarge_img(&data->player.left, data->tilesize, data);
	enlarge_img(&data->floor, data->tilesize, data);
	enlarge_img(&data->wall, data->tilesize, data);
	enlarge_img(&data->exit, data->tilesize, data);
	enlarge_img(&data->item, data->tilesize, data);
}

void	draw_map_on_window(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < data->y)
	{
		j = 0;
		while (j < data->x)
		{
			if (data->map[i][j] == '0' || data->map[i][j] == 'P')
				draw_tile(&data->floor, j, i, data);
			else if (data->map[i][j] == '1')
				draw_tile(&data->wall, j, i, data);
			else if (data->map[i][j] == 'E')
				draw_tile(&data->exit, j, i, data);
			else if (data->map[i][j] == 'C')
				draw_tile(&data->item, j, i, data);
			if (data->player.x == j && data->player.y == i)
				change_player_img_match_direction(&data->player, data);
			j++;
		}
		i++;
	}
}
