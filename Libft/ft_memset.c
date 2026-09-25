/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:01:51 by mvachon           #+#    #+#             */
/*   Updated: 2024/11/07 10:20:20 by mvachon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (n != i)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
// int main(void)
// {
//   char str[20] = "Hello World";
//   printf("%s", ft_memset(str, 'i' , 5));
// }