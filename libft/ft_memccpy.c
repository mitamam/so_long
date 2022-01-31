/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 22:30:20 by mmasuda           #+#    #+#             */
/*   Updated: 2021/04/19 10:43:34 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;
	unsigned char		*s;
	unsigned char		char_c;
	unsigned char		tmp;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	char_c = (unsigned char)c;
	if (!dst && !src)
		return (NULL);
	while (n-- > 0)
	{
		tmp = *s++;
		*d++ = tmp;
		if (tmp == char_c)
			return (d);
	}
	return (NULL);
}
