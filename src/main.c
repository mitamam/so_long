/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 22:23:46 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/08 09:55:30 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <so_long.h>

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
	draw_map_on_window(&data);
	display_number_of_steps(&data);
	// ------- delete below ------- //
	printf("floor size_line: %d\n", data.floor.line_length);
	printf("player front size_line: %d\n", data.player.front.line_length);
	printf("item size_line: %d\n", data.item.line_length);
	printf("exit size_line: %d\n", data.exit.line_length);
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
