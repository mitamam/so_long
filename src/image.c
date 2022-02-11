/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 05:48:11 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/10 07:48:12 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	composite_img(t_img *img, t_img *bg)
{
	long long	i;

	i = 0;
	while (i < (img->width * img->height))
	{
		if (img->addr[i] >= 0xFF000000)
			img->addr[i] = bg->addr[i];
		i++;
	}
}

void	initialize_large_img(t_img *large, size_t tilesize, t_data *data)
{
	large->img_ptr = mlx_new_image(data->mlx, tilesize, tilesize);
	if (large->img_ptr == NULL)
		display_map_error(MLX_ERROR, data);
	large->addr = (unsigned int *)mlx_get_data_addr(large->img_ptr,
			&large->bits_per_pixel, &large->line_length, &large->endian);
}

void	enlarge_img(t_img *img, size_t tilesize, t_data *data)
{
	t_img	large;
	double	ratio;
	size_t	i;
	size_t	j;

	i = 0;
	ratio = img->width / (double)tilesize;
	initialize_large_img(&large, tilesize, data);
	while (i < tilesize)
	{
		j = 0;
		while (j < tilesize)
		{
			data->fx = (int)ft_floor(j * ratio);
			data->fy = (int)ft_floor(i * ratio);
			large.addr[(i * tilesize) + j] = img->addr[
				(data->fy * img->width) + data->fx];
			j++;
		}
		i++;
	}
	large.path = img->path;
	mlx_destroy_image(data->mlx, img->img_ptr);
	*img = large;
}

void	load_image_from_xpm_file(t_data *data, t_img *img)
{
	img->img_ptr = mlx_xpm_file_to_image(data->mlx, img->path,
			&img->width, &img->height);
	if (img->img_ptr == NULL)
		display_map_error(MLX_ERROR, data);
	img->addr = (unsigned int *)mlx_get_data_addr(img->img_ptr,
			&img->bits_per_pixel, &img->line_length, &img->endian);
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
