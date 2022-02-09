/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 05:51:14 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/09 05:19:14 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	change_player_img_match_direction(t_player *player, t_data *data)
{
	size_t current_x;
	size_t current_y;

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

t_bool is_new_position_off_map_or_wall(int dx, int dy, t_data *data)
{
	size_t new_x;
	size_t new_y;

	new_x = data->player.x + dx;
	new_y = data->player.y + dy;
	if (new_x >= data->x || new_y >= data->y || data->map[new_y][new_x] == '1')
		return (true);
	return (false);
}

void	save_map_with_gnl(t_data *data)
{
	int		fd;
	int		ret;
	coord	y;
	char	*line;

	y = 0;
	ret = 1;
	fd = open(data->filename, O_RDONLY);
	data->map = (char **)malloc(sizeof(char *) * (data->y + 1));
	if (data->map == NULL || fd == -1)
		display_error(data);
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (line == NULL)
			display_map_error(UNKNOWN_ERROR, data);
		data->map[y] = ft_strdup(line);
		if (data->map[y] == NULL)
			display_map_error(UNKNOWN_ERROR, data);
		free(line);
		y++;
	}
	data->map[y] = NULL;
	close(fd);
}

void	parse_map_from_file(t_data *data)
{
	int		fd;
	int		ret;
	char	*buf;

	ret = 1;
	fd = open(data->filename, O_RDONLY);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL || fd == -1)
		display_error(data);
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buf);
			display_error(data);
		}
		buf[ret] = '\0';
		count_object(buf, data);
	}
	free(buf);
	close(fd);
}
