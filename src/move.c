/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 06:06:43 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/10 07:45:42 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

t_bool	is_new_position_off_map_or_wall(int dx, int dy, t_data *data)
{
	size_t	new_x;
	size_t	new_y;

	new_x = data->player.x + dx;
	new_y = data->player.y + dy;
	if (new_x >= data->x || new_y >= data->y || data->map[new_y][new_x] == '1')
		return (true);
	return (false);
}

void	change_player_img_match_direction(t_player *player, t_data *data)
{
	size_t	current_x;
	size_t	current_y;

	current_x = data->player.x;
	current_y = data->player.y;
	if (player->move == UP)
		draw_tile(&data->player.back, current_x, current_y, data);
	else if (player->move == LEFT)
		draw_tile(&data->player.left, current_x, current_y, data);
	else if (player->move == DOWN)
		draw_tile(&data->player.front, current_x, current_y, data);
	else if (player->move == RIGHT)
		draw_tile(&data->player.right, current_x, current_y, data);
}

void	move(t_move move, int dx, int dy, t_data *data)
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
