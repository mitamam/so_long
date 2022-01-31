/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 22:30:20 by mmasuda           #+#    #+#             */
/*   Updated: 2021/04/18 23:40:56 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_num(long num, int *minus)
{
	int	digit;

	digit = 0;
	if (num == 0)
		digit++;
	if (num < 0)
	{
		num *= -1;
		*minus = 1;
		digit++;
	}
	while (num > 0)
	{
		num /= 10;
		digit++;
	}
	return (digit);
}

static char	*calc_itoa(long num, int minus, int digit)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)malloc((sizeof(char) * (digit + 1)));
	if (!str)
		return (NULL);
	if (minus)
	{
		str[0] = '-';
		num *= -1;
	}
	if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[digit - i - 1] = num % 10 + '0';
		num /= 10;
		i++;
	}
	str[digit] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	long	num;
	int		digit;
	int		minus;

	num = (long)n;
	digit = 0;
	minus = 0;
	digit = check_num(num, &minus);
	return (calc_itoa(num, minus, digit));
}
