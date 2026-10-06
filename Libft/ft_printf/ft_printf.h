/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:54:22 by camansou          #+#    #+#             */
/*   Updated: 2024/11/26 19:20:48 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_print_char(char c);
int	ft_print_str(char *str);
int	check_format(char c, va_list args);
int	ft_printf(const char *str, ...);
int	ft_print_int(int n);
int	ft_print_unsigned(unsigned int n);
int	ft_print_hex(unsigned long n, char format);
int	ft_print_ptr(unsigned long long ptr);

#endif