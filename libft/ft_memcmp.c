/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 22:30:20 by mmasuda           #+#    #+#             */
/*   Updated: 2021/04/19 11:17:43 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char		char_s1;
	unsigned char		char_s2;

	while (n > 0)
	{
		char_s1 = *(unsigned char *)s1++;
		char_s2 = *(unsigned char *)s2++;
		if (char_s1 != char_s2)
			return (char_s1 - char_s2);
		n--;
	}
	return (0);
}
