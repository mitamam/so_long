/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 22:23:46 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/01 16:41:56 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <so_long.h>

void destroy_and_free_img(t_data *data, t_img *img)
{
	if (img->path != NULL)
		free(img->path);
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

	i = 0;
	while (i < (data->y + 3))
		free(data->dfs_map[i++]);
	free(data->dfs_map);
	i = 0;
	while (i < (data->y + 1))
		free(data->map[i++]);
	free(data->map);
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

void	display_error(t_data *data)
{
	printf("./so_long: %s: %s\n", data->filename, strerror(errno));
	exit_game(data, 1);
}

void	display_map_error(const t_errors error, t_data *data)
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
	exit_game(data, 1);
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

void draw_tile(t_img *img, size_t x, size_t y, t_data *data)
{
	size_t put_x;
	size_t put_y;
	
	put_x = data->tilesize * x;
	put_y = data->tilesize * y;
	mlx_put_image_to_window(data->mlx, data->mlx_win, img->img_ptr, put_x, put_y);
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

void	initialize_data(t_data *data, char *filename)
{
	data->filename = filename;
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->map = NULL;
	data->x = 0;
	data->y = 1;
	data->tilesize = 0;
	data->steps = 0;
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
	close(fd);
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

char *ft_strjoinjoin(char const *s1, char const *s2, char const *s3)
{
	char	*newstr;
	size_t	src_len;
	size_t	i;

	newstr = NULL;
	src_len = 0;
	i = 0;
	if (s1 == NULL || s2 == NULL || s3 == NULL)
		return (NULL);
	src_len += ft_strlen(s1);
	src_len += ft_strlen(s2);
	src_len += ft_strlen(s3);
	newstr = (char *)malloc(sizeof(char) * (src_len + 1));
	if (newstr == NULL)
		return (NULL);
	while (*s1 != '\0')
		newstr[i++] = *s1++;
	while (*s2 != '\0')
		newstr[i++] = *s2++;
	while (*s3 != '\0')
		newstr[i++] = *s3++;
	newstr[i] = '\0';
	return (newstr);
}

void *ft_memset_with_malloc(int c, size_t n)
{
	char *newstr;

	newstr = (char *)malloc(sizeof(char) * (n + 1));
	if (newstr == NULL)
		return (NULL);
	newstr[n] = '\0';
	return (ft_memset(newstr, c, n));
}

void	initialize_dfs_map(t_data *data)
{
	size_t	i;

	i = 0;
	data->dfs_map = (char **)malloc(sizeof(char) * data->y + 3);
	if (data->dfs_map == NULL)
		display_map_error(MALLOC_ERROR, data);
	data->dfs_map[0] = ft_memset_with_malloc('!', data->x + 2);
	data->dfs_map[data->y + 1] = ft_memset_with_malloc('!', data->x + 2);
	if (data->dfs_map[0] == NULL || data->dfs_map[data->y + 1] == NULL)
		display_map_error(MALLOC_ERROR, data);
	while (i < data->y)
	{
		data->dfs_map[i + 1] = ft_strjoinjoin("!", data->map[i], "!");
		if (data->dfs_map[i + 1] == NULL)
			display_map_error(MALLOC_ERROR, data);
		i++;
	}
	data->dfs_map[i + 2] = NULL;
}

void dfs(char **dfs_map, size_t x, size_t y, int *check)
{
	if (dfs_map[y][x] == '!' || *check == 1)
	{
		*check = 1;
		return ;
	}
	dfs_map[y][x] = 'P';
	if (dfs_map[y + 1][x] != '1' && dfs_map[y + 1][x] != 'P')
		dfs(dfs_map, x, y + 1, check);
	if (dfs_map[y - 1][x] != '1' && dfs_map[y - 1][x] != 'P')
		dfs(dfs_map, x, y - 1, check);
	if (dfs_map[y][x + 1] != '1' && dfs_map[y][x + 1] != 'P')
		dfs(dfs_map, x + 1, y, check);
	if (dfs_map[y][x - 1] != '1' && dfs_map[y][x - 1] != 'P')
		dfs(dfs_map, x - 1, y, check);
}

void	check_with_dfs_if_map_is_closed(t_data *data)
{
	int		check;
	size_t	dfs_x;
	size_t	dfs_y;

	check = 0;
	dfs_x = data->player.x + 1;
	dfs_y = data->player.y + 1;
	dfs(data->dfs_map, dfs_x, dfs_y, &check);
	if (check == 1)
		display_map_error(NOT_ENCLOSED, data);
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
	check_with_dfs_if_map_is_closed(data);
	if (error != -1)
		display_map_error(error, data);
}

void load_image_from_xpm_file(t_data *data, t_img *img)
{
	img->img_ptr = mlx_xpm_file_to_image(data->mlx, img->path, &img->width, &img->height);
	if (img->img_ptr == NULL)
	{
		printf("%s\n", strerror(errno)); // ------ delete ------ //
		display_map_error(MLX_ERROR, data);
	}
	img->addr = (unsigned int *)mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, &img->line_length, &img->endian);
}

void	initialize_mlx(t_data *data)
{
	data->mlx = mlx_init();
	load_image_from_xpm_file(data, &data->floor);
	load_image_from_xpm_file(data, &data->wall);
	load_image_from_xpm_file(data, &data->exit);
	load_image_from_xpm_file(data, &data->item);
	load_image_from_xpm_file(data, &data->player.front);
	load_image_from_xpm_file(data, &data->player.back);
	load_image_from_xpm_file(data, &data->player.right);
	load_image_from_xpm_file(data, &data->player.left);
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

void move(t_move move, int dx, int dy, t_data *data)
{
	data->player.move = move;
	data->pressed_flag = true;
	if (is_new_position_off_map_or_wall(dx, dy, data))
		return ;
	// ------------ delete ------------ //
	printf("current_x: %ld current_y: %ld\n", data->player.x, data->player.y);
	// ------------ end --------------- //
	if (data->map[data->player.y][data->player.x] == 'E')
		draw_tile(&data->exit, data->player.x, data->player.y, data);
	else
		draw_tile(&data->floor, data->player.x, data->player.y, data);
	data->steps++;
	data->player.x += dx;
	data->player.y += dy;
}

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

int	game_loop(t_data *data)
{
	if (data->pressed_flag == true)
	{
		change_player_img_match_direction(&data->player, data);
		if (data->map[data->player.y][data->player.x] == 'C')
		{
			data->collectibles--;
			// ------- delete ------- //
			printf("collectibles: %ld\n", data->collectibles);
			// -------- end ------- //
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

void	create_new_window(t_data *data)
{
	int	sizex;
	int	sizey;
	size_t	tile_w;
	size_t	tile_h;

	mlx_get_screen_size(data->mlx, &sizex, &sizey);
	tile_w = sizex / data->x;
	tile_h = sizey / data->y;
	if (tile_w < tile_h)
		data->tilesize = tile_w;
	else
		data->tilesize = tile_h;
	// ------- delete ------- //
	printf("sizex: %d sizey: %d\n", sizex, sizey); 
	printf("tilesize: %ld\n", data->tilesize);
	printf("windowx: %ld windowy: %ld\n", (data->tilesize * data->x), (data->tilesize * data->y));
	// --------- end ---------//
	data->mlx_win = mlx_new_window(data->mlx, (data->tilesize * data->x), (data->tilesize * data->y), "so_long");
	if (data->mlx_win == NULL)
		display_map_error(MLX_ERROR, data);
}

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

void draw_map_on_window(t_data *data)
{
	size_t	i;
	size_t	j;

	composite_img(&data->player.front, &data->floor);
	composite_img(&data->player.back, &data->floor);
	composite_img(&data->player.right, &data->floor);
	composite_img(&data->player.left, &data->floor);
	composite_img(&data->exit, &data->floor);
	composite_img(&data->item, &data->floor);
	i = 0;
	while (i < data->y)
	{
		j = 0;
		while (j < data->x)
		{
			if (data->map[i][j] == '0')
				draw_tile(&data->floor, j, i, data);
			else if (data->map[i][j] == '1')
				draw_tile(&data->wall, j, i, data);
			else if (data->map[i][j] == 'E')
				draw_tile(&data->exit, j, i, data);
			else if (data->map[i][j] == 'C')
				draw_tile(&data->item, j, i, data);
			else if (data->map[i][j] == 'P')
			{
				data->player.x = j;
				data->player.y = i;
				draw_tile(&data->player.front, j, i, data);
			}
			j++;
		}
		i++;
	}
}

void	count_number_of_digits(int *digits, size_t n)
{
	n /= 10;
	while (n > 0)
	{
		n /= 10;
		*digits += 1;
	}
}

char *ft_itoa_size_t(size_t n)
{
	size_t	i;
	int		digits;
	char	*converted;
	
	i = 0;
	digits = 1;
	converted = NULL;
	count_number_of_digits(&digits, n);
	converted = (char *)malloc(sizeof(char) * (digits + 1));
	if (converted == NULL)
		return (NULL);
	converted[0] = '0';
	while (n > 0)
	{
		converted[digits- i - 1] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	converted[digits] = '\0';
	return (converted);
}

void	display_number_of_steps(t_data *data)
{
	char *steps;

	steps = ft_itoa_size_t(data->steps);
	if (steps == NULL)
		return ;
	mlx_string_put(data->mlx, data->mlx_win, data->tilesize, data->tilesize, 255, "steps: ");
	mlx_string_put(data->mlx, data->mlx_win, data->tilesize * 3, data->tilesize, 255, steps);
	free(steps);
}

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (argc != 2)
		display_map_error(INCORRECT_ARG, NULL);
	initialize_data(&data, argv[1]);
	parse_map_from_file(&data);
	save_map_with_gnl(&data);
	initialize_dfs_map(&data);
	check_error_on_map(&data);
	initialize_mlx(&data);
	create_new_window(&data);
	draw_map_on_window(&data);
	display_number_of_steps(&data);
	// ------- delete below ------- //
	printf("y: %ld\n", data.y);
	printf("x: %ld\n", data.x);
	printf("collectibles: %ld\n", data.collectibles);
	printf("exits: %ld\n", data.exits);
	printf("start_position: %ld\n", data.start_position);
	printf("map: \n");
	size_t i = 0;
	while (data.map[i] != NULL)
		printf("%s\n", data.map[i++]);
	printf("dfsmap: \n");
	i = 0;
	while (data.dfs_map[i] != NULL)
		printf("%s\n", data.dfs_map[i++]);
	// ---------- end --------- //
	mlx_hook(data.mlx_win, 2, (1L << 0), &pressed_key, &data);
	mlx_hook(data.mlx_win, 33, (1L << 17), &close_window, &data);
	mlx_loop_hook(data.mlx, &game_loop, &data);
	mlx_loop(data.mlx);
	exit_game(&data, 0);
	return (0);
}
