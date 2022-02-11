/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 05:43:21 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/10 07:48:36 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	initialize_dfs_map(t_data *data)
{
	size_t	i;

	i = 0;
	data->dfs_map = (char **)malloc(sizeof(char *) * (data->y + 3));
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

void	dfs(char **dfs_map, size_t x, size_t y, int *check)
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
