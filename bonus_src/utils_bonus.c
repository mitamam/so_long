/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 07:46:28 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/10 07:49:11 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long_bonus.h>

double	ft_floor(double x)
{
	int	dx;

	dx = (int)x;
	if (x > 0.0 || dx <= x)
		return (dx);
	return ((int)x - 1.0);
}

char	*ft_strjoinjoin(char const *s1, char const *s2, char const *s3)
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

void	*ft_memset_with_malloc(int c, size_t n)
{
	char	*newstr;

	newstr = (char *)malloc(sizeof(char) * (n + 1));
	if (newstr == NULL)
		return (NULL);
	ft_memset(newstr, c, n);
	newstr[n] = '\0';
	return (newstr);
}

void	count_number_of_digits(int *digits, size_t n)
{
	*digits = 1;
	n /= 10;
	while (n > 0)
	{
		n /= 10;
		*digits += 1;
	}
}

char	*ft_itoa_size_t(size_t n)
{
	size_t	i;
	int		digits;
	char	*converted;

	i = 0;
	digits = 1;
	converted = NULL;
	count_number_of_digits(&digits, n);
	converted = (char *)malloc(sizeof(char) * (digits + 1));
	if (converted == NULL)
		return (NULL);
	converted[0] = '0';
	while (n > 0)
	{
		converted[digits - i - 1] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	converted[digits] = '\0';
	return (converted);
}
