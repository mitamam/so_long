/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 06:06:43 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/09 05:12:15 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void move(t_move move, int dx, int dy, t_data *data)
{
	data->player.move = move;
	data->pressed_flag = true;
	if (is_new_position_off_map_or_wall(dx, dy, data))
		return ;
	if (data->map[data->player.y][data->player.x] == 'E')
		draw_tile(&data->exit, data->player.x, data->player.y, data);
	else
		draw_tile(&data->floor, data->player.x, data->player.y, data);
	data->steps++;
	printf("steps: %ld\n", data->steps);
	data->player.x += dx;
	data->player.y += dy;
}

int	pressed_key(int key_code, t_data *data)
{
	if (key_code == KEY_W)
		move(UP, 0, -1, data);
	else if (key_code == KEY_A)
		move(LEFT, -1, 0, data);
	else if (key_code == KEY_S)
		move(DOWN, 0, 1, data);
	else if (key_code == KEY_D)
		move(RIGHT, 1, 0, data);
	else if (key_code == KEY_ESC)
		exit_game(data, 0);
	return (0);
}
