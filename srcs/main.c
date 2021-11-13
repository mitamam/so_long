/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:17:16 by mmasuda           #+#    #+#             */
/*   Updated: 2021/11/11 12:14:48 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	display_error(const t_errors error, t_mlx *mlx)
{
	const char	*error_msgs[INVALID] = {
		"usage: ./so_long [ .ber mapfile ]",
		"map file must have a .ber extension",
		"open error",
		"map is not rectangular in shape",
		"map is not enclosed by walls",
		"map must have at least one exit",
		"map must have a starting position for the player",
		"map must have at least one collectible",
		"multiple starting positions exists on the map",
		"malloc error",
	};
	printf("Error\n");
	if (error == INCORRECT_ARG)
		printf("%s\n", error_msgs[error]);
	else if (error == MALLOC_ERROR || error == OPEN_ERROR)
		printf("%s\n", strerror(errno));
	else
		printf("%s: %s\n", mlx->map.filename, error_msgs[error]);
	exit(1);
}

t_bool is_file_extention_ber(const char *filename)
{
	int filename_length;
	
	filename_length = ft_strlen(filename);
	if (filename_length >= 4 && ft_strncmp(".ber", &filename[filename_length - 4], 4) == 0)
		return (true);
	else
		return (false);
}

t_bool is_not_map_rectangular(const t_map map, const long prev_line_x)
{
	return (map.x != prev_line_x && map.y != 0);
}

void	validate_arguments(int argc, char **argv, t_mlx *mlx)
{
	mlx->map.filename = argv[1];
	if (argc != 2)
		display_error(INCORRECT_ARG, mlx);
	else if (!is_file_extention_ber(argv[1]))
		display_error(INCORRECT_EXT, mlx);
}

void	initialize_mlx(t_mlx *mlx)
{
	mlx->win_width = mlx->map.x * TILE_SIZE;
	mlx->win_height = mlx->map.y * TILE_SIZE;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->win_width, mlx->win_height, "so_long");
}

void	initialize_map(t_map *map)
{
	map->x = 0;
	map->y = 0;
	map->collectibles = 0;
}

void	read_map(t_mlx *mlx)
{
	long prev_line_x;

	prev_line_x = 0;
	mlx->map.fd = open(mlx->map.filename, O_RDONLY);
	if (mlx->map.fd == -1)
		display_error(OPEN_ERROR, mlx);
	while (mlx->map.x != -1)
	{
		mlx->map.x = get_next_line(mlx->map.fd, &(mlx->map.map[mlx->map.y]));
		if (is_not_map_rectangular(mlx->map, prev_line_x))
			display_error(NOT_RECTANGLE, mlx);
		prev_line_x = mlx->map.x;
		mlx->map.y++;
	}
}

int main(int argc, char **argv)
{
	t_mlx mlx;

	validate_arguments(argc, argv, &mlx);
	read_map(&mlx);
	initialize_map(&(mlx.map));
	initialize_mlx(&mlx);
}