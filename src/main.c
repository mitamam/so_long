/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 22:23:46 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/09 14:06:15 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <so_long.h>

int	expose_window(t_data *data)
{
	draw_map_on_window(data);
	display_number_of_steps(data);
	return (0);
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
	composite_and_enlarge_img(&data);
	mlx_hook(data.mlx_win, X_EVENT_KEY_PRESS, (1L<<0), &pressed_key, &data);
	mlx_hook(data.mlx_win, X_EVENT_EXPOSE, (1L<<15), &expose_window, &data);
	mlx_hook(data.mlx_win, X_EVENT_RED_CROSS, (1L<<17), &close_window, &data);
	mlx_loop_hook(data.mlx, &game_loop, &data);
	mlx_loop(data.mlx);
	exit_game(&data, 0);
	return (0);
}
