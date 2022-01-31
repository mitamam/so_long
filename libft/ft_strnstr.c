/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 22:30:20 by mmasuda           #+#    #+#             */
/*   Updated: 2021/04/19 22:05:04 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	needle_len;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	while (i < len && haystack[i])
	{
		j = 0;
		while (j < needle_len && (i + j) < len)
		{
			if (haystack[i + j] != needle[j])
				break ;
			j++;
		}
		if (j == needle_len)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
