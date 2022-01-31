/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 22:23:46 by mmasuda           #+#    #+#             */
/*   Updated: 2022/01/31 21:59:35 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <so_long.h>

void	display_error(t_data *data)
{
	printf("./so_long: %s: %s\n", data->filename, strerror(errno));
	// free memory
	exit(1);
}

void	display_map_error(const t_errors error, const t_data *data)
{
	const char	*error_msgs[INVALID] = {
		"usage: ./so_long [ .ber mapfile ]",
		"map file must have a .ber extension",
		"map is not rectangular in shape",
		"map is not enclosed by walls",
		"map must have at least one exit",
		"map must have a starting position for the player",
		"map must have at least one collectible",
		"multiple starting positions exists on the map",
		"invalid characters on the map",
		"a malloc error has occurred",
		"an error occurred in MiniLibX",
		"an unknown error has occurred",
	};
	
	printf("Error\n");
	if (error == INCORRECT_ARG || error >= MALLOC_ERROR)
		printf("%s\n", error_msgs[error]);
	else
		printf("%s: %s\n", data->filename, error_msgs[error]);
	// free memory
	exit(1);
}

t_bool	is_line_length_same_as_prev_line(const coord line_length, const coord x)
{
	if (line_length == x)
		return (true);
	else
		return (false);
}

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

t_img	initialize_img(t_data *data, char *img_name)
{
	t_img	empty_img;

	empty_img.img = NULL;
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

void	initialize_data(t_data *data, char *filename)
{
	data->filename = filename;
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->map = NULL;
	data->x = 0;
	data->y = 1;
	data->tile_w = 0;
	data->tile_h = 0;
	data->steps = 0;
	data->collectibles = 0;
	data->exits = 0;
	data->start_position = 0;
	data->player.front = initialize_img(data, "front.xpm");
	data->player.back = initialize_img(data, "back.xpm");
	data->player.right = initialize_img(data, "right.xpm");
	data->player.left = initialize_img(data, "left.xpm");
	data->floor = initialize_img(data, "floor.xpm");
	data->wall = initialize_img(data, "wall.xpm");
	data->exit = initialize_img(data, "exit.xpm");
	data->item = initialize_img(data, "item.xpm");
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
		buf[ret] = '\0';
		count_object(buf, data);
	}
	if (ret == -1)
		display_error(data);
	free(buf);
	close(fd);
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
}

int	check_rectangular_and_invalid_char(t_data *data)
{
	coord	x;
	coord	y;

	y = 0;
	while (data->map[y] != NULL)
	{
		x = 0;
		while (data->map[y][x] != '\0')
		{
			if (data->map[y][x] != '0' && data->map[y][x] != '1' &&
			 data->map[y][x] != 'C' && data->map[y][x] != 'E' &&
			 data->map[y][x] != 'P')
				return (INVALID_CHARACTER);
			x++;
		}
		if (y == 0)
			data->x = x;
		else if (data->x != x)
			return (NOT_RECTANGULAR);
		y++;
	}
	return (-1);
}

t_bool	is_file_extension_incorrect(t_data *data)
{
	if (ft_strncmp(ft_strrchr(data->filename, '.'), ".ber", 4) != 0)
		return (true);
	return (false);
}

void	check_error_on_map(t_data *data)
{
	int	error;

	error = -1;
	if (is_file_extension_incorrect(data))
		error = INCORRECT_EXT;
	else if (data->collectibles == 0)
		error = NO_COLLECTIBLES;
	else if (data->exits == 0)
		error = NO_EXIT;
	else if (data->start_position == 0)
		error = NO_START_POSITION;
	else if (data->start_position > 1)
		error = MULTIPLE_START_POSITION;
	else
		error = check_rectangular_and_invalid_char(data);
	// --------------- check map enclosed with dfs ------------- //
	if (error != -1)
		display_map_error(error, data);
}

void load_image_from_xpm_file(t_data *data, t_img *img)
{
	img->img = mlx_xpm_file_to_image(data->mlx, img->path, &(img->width), &(img->height));
	if (img->img == NULL)
	{
		printf("%s\n", strerror(errno)); // ------ delete ------ //
		display_map_error(MLX_ERROR, data);
	}
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel), &(img->line_length), &(img->endian));
}

void	initialize_mlx(t_data *data)
{
	data->mlx = mlx_init();
	load_image_from_xpm_file(data, &(data->floor));
	load_image_from_xpm_file(data, &(data->wall));
	load_image_from_xpm_file(data, &(data->exit));
	load_image_from_xpm_file(data, &(data->item));
	load_image_from_xpm_file(data, &(data->player.front));
	load_image_from_xpm_file(data, &(data->player.back));
	load_image_from_xpm_file(data, &(data->player.right));
	load_image_from_xpm_file(data, &(data->player.left));
}

int	close_window(void *param)
{
	(void)param;
	exit(0);
}

void	create_new_window(t_data *data)
{
	int	sizex;
	int	sizey;

	mlx_get_screen_size(data->mlx, &sizex, &sizey);
	data->tile_w = sizex / data->x;
	data->tile_h = sizex / data->y;
	// ------- delete ------- //
	printf("sizex: %d, sizey: %d\n", sizex, sizey); 
	printf("tile_w: %d, tile_h: %d\n", tile_w, tile_h);
	printf("windowx: %d, windowy: %d\n", (data->tile_w * data->x), (data->tile_h * data->y));
	// --------- end ---------//
	data->mlx_win = mlx_new_window(data->mlx, (data->tile_w * data->x), (data->tile_h * data->y), "so_long");
	if (data->mlx_win == NULL)
		display_map_error(MLX_ERROR, data);
	// mlx_hook(data->mlx_win, 2, (1L << 0), &key_press, &data);
	mlx_hook(data->mlx_win, 33, (1L << 17), &close_window, (void *)0);
	// mlx_loop_hook(map.mlx_ptr, &map_loop, &map);
	mlx_loop(data->mlx);
}

void destroy_and_free_img(t_data *data, t_img *img)
{
	free(img->path);
	mlx_destroy_image(data->mlx, img);
	free(img);
}

void	free_data(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->map[i] != NULL)
		free(data->map[i++]);
	destroy_and_free_img(data, &(data->floor));
	destroy_and_free_img(data, &(data->wall));
	destroy_and_free_img(data, &(data->exit));
	destroy_and_free_img(data, &(data->item));
	destroy_and_free_img(data, &(data->player.front));
	destroy_and_free_img(data, &(data->player.back));
	destroy_and_free_img(data, &(data->player.right));
	destroy_and_free_img(data, &(data->player.left));
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (argc != 2)
		display_map_error(INCORRECT_ARG, NULL);
	initialize_data(&data, argv[1]);
	parse_map_from_file(&data);
	save_map_with_gnl(&data);
	check_error_on_map(&data);
	initialize_mlx(&data);
	create_new_window(&data);
	// ------- delete below ------- //
	printf("y: %ld\n", data.y);
	printf("x: %ld\n", data.x);
	printf("collectibles: %ld\n", data.collectibles);
	printf("exits: %ld\n", data.exits);
	printf("start_position: %ld\n", data.start_position);
	int i = 0;
	while (data.map[i] != NULL)
		printf("%s\n", data.map[i++]);
	// ---------- end --------- //
	free_data(&data);
}
