/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 05:51:14 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/10 07:45:35 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long_bonus.h>

void	save_map_with_gnl(t_data *data)
{
	int		fd;
	int		ret;
	t_coord	y;
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
