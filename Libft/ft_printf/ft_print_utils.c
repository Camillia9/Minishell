/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:54:01 by camansou          #+#    #+#             */
/*   Updated: 2024/11/26 19:37:26 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_str(char *str)
{
	int	i;

	if (str == NULL)
		return (ft_print_str("(null)"));
	i = 0;
	while (str[i])
	{
		ft_print_char(str[i]);
		i++;
	}
	return (i);
}

int	ft_print_int(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		len += ft_print_char('-');
		n = -n;
	}
	if (n < 10)
		len += ft_print_char(n + '0');
	if (n >= 10)
	{
		len += ft_print_int(n / 10);
		len += ft_print_int(n % 10);
	}
	return (len);
}

int	ft_print_unsigned(unsigned int n)
{
	int	len;

	len = 0;
	if (n < 10)
		len += ft_print_char(n + '0');
	else
	{
		len += ft_print_unsigned(n / 10);
		len += ft_print_char((n % 10) + '0');
	}
	return (len);
}

int	ft_print_hex(unsigned long n, char format)
{
	int		len;
	char	*base;

	len = 0;
	if (format == 'x')
		base = "0123456789abcdef";
	else if (format == 'X')
		base = "0123456789ABCDEF";
	if (n < 16)
		len += ft_print_char(base[n]);
	else
	{
		len += ft_print_hex(n / 16, format);
		len += ft_print_char(base[n % 16]);
	}
	return (len);
}
