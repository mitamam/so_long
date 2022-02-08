/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 05:45:36 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/06 09:12:59 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	count_object(char *buf, t_data *data)
{
	size_t	i;

	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			data->y++;
		else if (buf[i] == 'C')
			data->collectibles++;
		else if (buf[i] == 'E')
			data->exits++;
		else if (buf[i] == 'P')
			data->start_position++;
		i++;
	}
}

void	initialize_data(t_data *data, char *filename)
{
	data->filename = filename;
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->map = NULL;
	data->x = 0;
	data->y = 1;
	data->string_y = 0;
	data->tilesize = 0;
	data->steps = 0;
	data->steps_digits = 1;
	data->collectibles = 0;
	data->exits = 0;
	data->start_position = 0;
	data->player.front = initialize_img(data, "front.xpm");
	data->player.back = initialize_img(data, "back.xpm");
	data->player.right = initialize_img(data, "right.xpm");
	data->player.left = initialize_img(data, "left.xpm");
	data->player.x = 0;
	data->player.y = 0;
	data->player.move = DOWN;
	data->floor = initialize_img(data, "floor.xpm");
	data->wall = initialize_img(data, "wall.xpm");
	data->exit = initialize_img(data, "exit.xpm");
	data->item = initialize_img(data, "item.xpm");
}
