/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 23:21:10 by mmasuda           #+#    #+#             */
/*   Updated: 2021/04/29 23:20:59 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strchr_idx(const char *s, int c)
{
	unsigned char	char_c;
	int				i;

	char_c = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == char_c)
			return (i);
		i++;
	}
	if (s[i] == char_c)
		return (i);
	return (-1);
}

int	ft_read(int fd, char **save)
{
	char	*buf;
	char	*tmp;
	int		ret;

	ret = 0;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	while (ret >= 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret >= 0)
			buf[ret] = '\0';
		if (ret == 0 || ret == -1)
			break ;
		tmp = ft_strjoin(*save, buf);
		free(*save);
		*save = tmp;
		if ((ft_strchr_idx(*save, '\n')) >= 0)
			break ;
	}
	free(buf);
	if (ret > 0)
		return (1);
	return (ret);
}

char	*ft_result_if_else(char **line, char *save, int result, int *tosave)
{
	if (result < 0)
	{
		*line = NULL;
		return (NULL);
	}
	else if (result == 0)
	{
		if (!save)
		{
			*line = ft_substr("", 0, 0);
			return (NULL);
		}
		*tosave = ft_strlen(save);
		return (NULL);
	}
	else
	{
		*tosave = ft_strchr_idx(save, '\n');
		return (ft_strdup(save + (*tosave) + 1));
	}
}

int	get_next_line(int fd, char **line)
{
	static char	*save[256];
	char		*tmp;
	int			tosave;
	int			result;

	result = 1;
	tosave = 0;
	if (fd < 0 || 255 < fd || !line || BUFFER_SIZE <= 0)
	{
		*line = NULL;
		return (-1);
	}
	if (!save[fd] || ft_strchr_idx(save[fd], '\n') < 0)
		result = ft_read(fd, &save[fd]);
	tmp = ft_result_if_else(line, save[fd], result, &tosave);
	if ((tosave == 0 && !tmp && !save[fd]) || result == -1)
		return (result);
	*line = ft_substr(save[fd], 0, tosave);
	free(save[fd]);
	save[fd] = tmp;
	return (result);
}
