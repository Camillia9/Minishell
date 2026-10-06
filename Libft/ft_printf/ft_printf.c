/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:16:44 by camansou          #+#    #+#             */
/*   Updated: 2024/11/30 14:01:49 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>

int	check_format(char c, va_list args)
{
	if (c == 'c')
		return (ft_print_char(va_arg(args, int)));
	else if (c == 's')
		return (ft_print_str(va_arg(args, char *)));
	else if (c == 'd' || c == 'i')
		return (ft_print_int(va_arg(args, int)));
	else if (c == 'u')
		return (ft_print_unsigned(va_arg(args, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), c));
	else if (c == '%')
		return (ft_print_char('%'));
	else if (c == 'p')
		return (ft_print_ptr(va_arg(args, unsigned long)));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;
	int		i;

	if (!str)
		return (-1);
	len = 0;
	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += check_format(str[i + 1], args);
			i++;
		}
		else
		{
			ft_print_char(str[i]);
			len++;
		}
		i++;
	}
	va_end(args);
	return (len);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char *str;
// 	str = NULL;
// 	printf("%s %d\n", str, 10);
// 	ft_printf("%s %d\n", str, 10);

// 	printf("n = %d\n", ft_printf("test %c, test2 %s, test3 %d, test4 %x, test5
// 			%X, test6 %%\n", 'z', "amo", (int)-2147483648, (unsigned int)255,
// 			(unsigned int)-2147483648));
// 	printf("n = %d\n", printf("test %c, test2 %s, test3 %d, test4 %x, test5 %X,
// 			test6 %%\n", 'z', "amo", (int)-2147483648, (unsigned int)255,
// 			(unsigned int)-2147483648));

// 	long p = LONG_MIN;
// 	long *ptr = &p;
// 	ft_printf("%p\n", ptr);
// 	printf("%p\n", ptr);

// 	return (0);
// }