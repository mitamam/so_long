/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 22:30:20 by mmasuda           #+#    #+#             */
/*   Updated: 2021/04/19 10:39:54 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_overflow(long num, char str)
{
	long	ov_div;
	long	ov_mod;

	ov_div = __LONG_MAX__ / 10;
	ov_mod = __LONG_MAX__ % 10;
	if (num > ov_div)
		return (-1);
	else if (num == ov_div && ((int)str - '0') > ov_mod)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		minus;
	long	num;

	i = 0;
	minus = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		num *= 10;
		num += (int)str[i] - '0';
		if (check_overflow(num, str[i + 1]) == -1)
			return (-1);
		i++;
	}
	return (num * minus);
}
