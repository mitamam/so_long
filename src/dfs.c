/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 05:43:21 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/04 07:49:19 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

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
	ft_memset(newstr, c, n);
	newstr[n] = '\0';
	return (newstr);
}

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

	// delete //
	size_t i = 0;
	while (i < data->y + 2)
		printf("%s\n", data->dfs_map[i++]);
	// end //
	check = 0;
	dfs_x = data->player.x + 1;
	dfs_y = data->player.y + 1;
	dfs(data->dfs_map, dfs_x, dfs_y, &check);
	if (check == 1)
		display_map_error(NOT_ENCLOSED, data);
}
