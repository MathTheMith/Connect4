/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:49:24 by mvachon           #+#    #+#             */
/*   Updated: 2024/11/16 16:10:10 by mvachon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_overflow(long long str, int b)
{
	if (str > LLONG_MAX / 10)
		return (1);
	if (str == LLONG_MAX / 10 && b > LLONG_MAX % 10)
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	size_t		i;
	int			sign;
	long long	str;

	i = 0;
	sign = 1;
	str = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (check_overflow(str, nptr[i] - '0'))
			return (0);
		str = str * 10 + (nptr[i] - '0');
		i++;
	}
	return (str * sign);
}

// #include <stdlib.h>
// int main(void)
// {
// 	char *str = "-1564546779879898798987456454546564";
//     printf("%d\n", ft_atoi((str)));
// 	printf("%d", atoi((str)));
// }