/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 07:42:36 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/10 07:43:49 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long_bonus.h>

int	close_window(t_data *data)
{
	exit_game(data, 0);
	return (0);
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

int	expose_window(t_data *data)
{
	draw_map_on_window(data);
	display_number_of_steps(data);
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
