/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 22:21:38 by hlachkar          #+#    #+#             */
/*   Updated: 2022/11/15 22:53:02 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n >= 0 && n <= 9)
		ft_putchar_fd(n + '0', fd);
	else if (n < 0)
	{
		write (fd, "-", 1);
		ft_putnbr_fd(n *= -1, fd);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	str_digit(char *str)
{
	while (str && *str)
	{
		if (!isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
