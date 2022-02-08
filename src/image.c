/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 05:48:11 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/08 13:07:32 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	composite_img(t_img *img, t_img *bg)
{
	long long i;

	i = 0;
	while (i < (img->width * img->height))
	{
		if (img->addr[i] >= 0xFF000000)
			img->addr[i] = bg->addr[i];
		i++;
	}
}

double ft_floor(double x)
{
	int dx;

	dx = (int)x;
	if (x > 0.0 || dx <= x)
		return dx;
	return (int)x - 1.0;
}

void enlarge_img(t_img *img, size_t tilesize, t_data *data)
{
	t_img enlarged;
	double ratio;
	size_t i;
	size_t j;
	int px;
	int py;

	i = 0;
	ratio = img->width / (double)tilesize;
	enlarged.img_ptr = mlx_new_image(data->mlx, tilesize, tilesize);
	enlarged.addr = (unsigned int *)mlx_get_data_addr(enlarged.img_ptr, 
		&enlarged.bits_per_pixel, &enlarged.line_length, &enlarged.endian);
	while (i < tilesize)
	{
		j = 0;
		while (j < tilesize)
		{
			px = (int)ft_floor(j * ratio);
			py = (int)ft_floor(i * ratio);
			enlarged.addr[(i * tilesize) + j] = img->addr[(py * img->width) + px];
			j++;
		}
		i++;
	}
	enlarged.path = img->path;
	mlx_destroy_image(data->mlx, img->img_ptr);
	*img = enlarged;
}

void load_image_from_xpm_file(t_data *data, t_img *img)
{
	img->img_ptr = mlx_xpm_file_to_image(data->mlx, img->path, &img->width, &img->height);
	if (img->img_ptr == NULL)
		display_map_error(MLX_ERROR, data);
	img->addr = (unsigned int *)mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, &img->line_length, &img->endian);
}

t_img	initialize_img(t_data *data, char *img_name)
{
	t_img	empty_img;

	empty_img.img_ptr = NULL;
	empty_img.path = ft_strjoin("textures/", img_name);
	if (empty_img.path == NULL)
		display_map_error(MALLOC_ERROR, data);
	empty_img.addr = NULL;
	empty_img.bits_per_pixel = 0;
	empty_img.line_length = 0;
	empty_img.endian = 0;
	empty_img.width = 0;
	empty_img.height = 0;
	return (empty_img);
}
