/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 22:30:20 by mmasuda           #+#    #+#             */
/*   Updated: 2021/04/19 22:06:32 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	s_len;

	s_len = 0;
	d_len = ft_strlen(dst);
	if (dstsize <= d_len)
	{
		s_len = ft_strlen(src);
		return (dstsize + s_len);
	}
	while (d_len < dstsize - 1 && dstsize > 0 && src[s_len])
		dst[d_len++] = src[s_len++];
	dst[d_len] = '\0';
	while (src[s_len++] != '\0')
		d_len++;
	return (d_len);
}
