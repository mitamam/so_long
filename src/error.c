/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 05:44:02 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/10 06:37:08 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	display_error(t_data *data)
{
	printf("Error/n");
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
	if (error == INCORRECT_ARG)
	{
		printf("%s\n", error_msgs[error]);
		exit(1);
	}
	else
		printf("%s: %s\n", data->filename, error_msgs[error]);
	exit_game(data, 1);
}

int	check_rectangular_and_invalid_char(t_coord *x, t_coord *y, t_data *data)
{
	while (data->map[*y] != NULL)
	{
		*x = 0;
		while (data->map[*y][*x] != '\0')
		{
			if (data->map[*y][*x] == 'P')
			{
				data->player.x = *x;
				data->player.y = *y;
			}
			if (data->map[*y][*x] != '0' && data->map[*y][*x] != '1' &&
				data->map[*y][*x] != 'C' && data->map[*y][*x] != 'E' &&
				data->map[*y][*x] != 'P')
				return (INVALID_CHARACTER);
			*x += 1;
		}
		if (*y == 0)
			data->x = *x;
		else if (data->x != *x)
			return (NOT_RECTANGULAR);
		*y += 1;
	}
	return (-1);
}

t_bool	is_file_extension_incorrect(t_data *data)
{
	char	*ext;

	ext = ft_strrchr(data->filename, '.');
	if (ext == NULL || ft_strncmp(ext, ".ber", 4) != 0)
		return (true);
	return (false);
}

void	check_error_on_map(t_data *data)
{
	int		error;
	t_coord	x;
	t_coord	y;

	error = -1;
	x = 0;
	y = 0;
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
		error = check_rectangular_and_invalid_char(&x, &y, data);
	if (error != -1)
		display_map_error(error, data);
	initialize_dfs_map(data);
	check_with_dfs_if_map_is_closed(data);
}
