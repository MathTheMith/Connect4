/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:16:21 by mvachon           #+#    #+#             */
/*   Updated: 2024/11/12 11:09:38 by mvachon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void    ft_putchar(char c, int fd)
{
    write(fd, &c, 1);
}

void    ft_putnbr_fd(int n, int fd)
{
    if (n == -2147483648)
    {
        ft_putchar('-', fd);
        ft_putnbr_fd(21, fd);
        ft_putnbr_fd(47483648, fd);
        return ;
    }
    if (n < 0)
    {
        ft_putchar('-', fd);
        n = n *(-1);
    }
    if (n >= 0 && n <= 9)
    {
        ft_putchar(n + '0', fd);
    }
    if (n > 9)
    {
        ft_putnbr_fd(n / 10, fd);
        ft_putnbr_fd(n % 10, fd);
    }
}
