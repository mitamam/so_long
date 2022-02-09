/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 05:57:37 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/09 05:48:41 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void destroy_and_free_img(t_data *data, t_img *img)
{
	if (img->img_ptr != NULL)
		mlx_destroy_image(data->mlx, img->img_ptr);
}

void free_all_img(t_data *data)
{
	destroy_and_free_img(data, &data->floor);
	destroy_and_free_img(data, &data->wall);
	destroy_and_free_img(data, &data->exit);
	destroy_and_free_img(data, &data->item);
	destroy_and_free_img(data, &data->player.front);
	destroy_and_free_img(data, &data->player.back);
	destroy_and_free_img(data, &data->player.right);
	destroy_and_free_img(data, &data->player.left);
}

void	exit_game(t_data *data, int ret)
{
	size_t	i;

	if (data->dfs_map != NULL)
	{
		i = 0;
		while (i < (data->y + 3))
			free(data->dfs_map[i++]);
		free(data->dfs_map);
	}
	if (data->map != NULL)
	{
		i = 0;
		while (i < (data->y + 1))
			free(data->map[i++]);
		free(data->map);
	}
	free_all_img(data);
	if (data->mlx_win != NULL)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx != NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(ret);
}
