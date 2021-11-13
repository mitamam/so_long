/* ************************************************************************** */
/*                                                                          */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 22:30:20 by mmasuda           #+#    #+#             */
/*   Updated: 2021/04/11 22:44:08 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t		bite_size;
	void		*buf;

	if (count == 0)
		count = 1;
	if (size == 0)
		size = 1;
	bite_size = count * size;
	buf = malloc(count * size);
	if (buf)
		ft_bzero(buf, bite_size);
	else
		return (NULL);
	return (buf);
}
