/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 06:00:23 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/08 13:38:43 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	count_number_of_digits(int *digits, size_t n)
{
	n /= 10;
	while (n > 0)
	{
		n /= 10;
		*digits += 1;
	}
}

char *ft_itoa_size_t(size_t n)
{
	size_t	i;
	int		digits;
	char	*converted;
	
	i = 0;
	digits = 1;
	converted = NULL;
	count_number_of_digits(&digits, n);
	converted = (char *)malloc(sizeof(char) * (digits + 1));
	if (converted == NULL)
		return (NULL);
	converted[0] = '0';
	while (n > 0)
	{
		converted[digits- i - 1] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	converted[digits] = '\0';
	return (converted);
}

void	display_number_of_steps(t_data *data)
{
	char *steps;
	size_t i;
	size_t j;
	size_t fill_width;

	i = 0;
	data->string_y = (data->tilesize * data->y) + 12;
	data->steps_digits = 1;
	count_number_of_digits(&data->steps_digits, data->steps);
	fill_width = data->steps_digits * 6;
	steps = ft_itoa_size_t(data->steps);
	if (steps == NULL)
		return ;
	while (i < 20)
	{
		j = 0;
		while (j++ < fill_width)
			mlx_pixel_put(data->mlx, data->mlx_win, 38 + j, data->string_y - 10 + i, 0x0);
		i++;
	}
	mlx_string_put(data->mlx, data->mlx_win, 0, data->string_y, 0xFFFFFF, "steps: ");
	mlx_string_put(data->mlx, data->mlx_win, 40, data->string_y + 1, 0xFFFFFF, steps);
	free(steps);
}

void draw_tile(t_img *img, size_t x, size_t y, t_data *data)
{
	size_t put_x;
	size_t put_y;
	
	put_x = data->tilesize * x;
	put_y = data->tilesize * y;
	mlx_put_image_to_window(data->mlx, data->mlx_win, img->img_ptr, put_x, put_y);
}

void composite_and_enlarge_img(t_data *data)
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

void draw_map_on_window(t_data *data)
{
	size_t	i;
	size_t	j;

	composite_and_enlarge_img(data);
	i = 0;
	while (i < data->y)
	{
		j = 0;
		while (j < data->x)
		{
			if (data->map[i][j] == '0')
				draw_tile(&data->floor, j, i, data);
			else if (data->map[i][j] == '1')
				draw_tile(&data->wall, j, i, data);
			else if (data->map[i][j] == 'E')
				draw_tile(&data->exit, j, i, data);
			else if (data->map[i][j] == 'C')
				draw_tile(&data->item, j, i, data);
			else if (data->map[i][j] == 'P')
				draw_tile(&data->player.front, j, i, data);
			j++;
		}
		i++;
	}
}
