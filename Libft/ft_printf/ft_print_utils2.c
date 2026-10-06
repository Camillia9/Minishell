/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:26:30 by camansou          #+#    #+#             */
/*   Updated: 2024/11/26 19:34:39 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_ptr(unsigned long long ptr)
{
	if (ptr == 0)
		return (ft_print_str("(nil)"));
	ft_print_str("0x");
	return (ft_print_hex((unsigned long)ptr, 'x') + 2);
}
