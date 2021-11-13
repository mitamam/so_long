/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 22:30:20 by mmasuda           #+#    #+#             */
/*   Updated: 2021/04/20 09:58:36 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_words(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*trim_str(size_t begin, size_t end, size_t len, char const *s1)
{
	char	*trimstr;
	size_t	i;

	i = 0;
	if (begin == len)
	{
		trimstr = (char *)malloc(sizeof(char));
		if (!trimstr)
			return (NULL);
		trimstr[0] = '\0';
		return (trimstr);
	}
	trimstr = (char *)malloc(sizeof(char) * (end - begin) + 1);
	if (trimstr)
	{
		while (i < (end - begin))
		{
			trimstr[i] = s1[begin + i];
			i++;
		}
		trimstr[i] = '\0';
		return (trimstr);
	}
	return (NULL);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begin;
	size_t	end;
	size_t	len;

	begin = 0;
	end = 0;
	len = 0;
	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	end = len;
	while (check_words(s1[begin], set))
		begin++;
	while (begin != end && check_words(s1[end - 1], set))
		end--;
	return (trim_str(begin, end, len, s1));
}
