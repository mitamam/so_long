/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 23:07:30 by mmasuda           #+#    #+#             */
/*   Updated: 2021/04/19 10:56:19 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	char_c;
	int				i;

	i = 0;
	char_c = (char)c;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == char_c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
