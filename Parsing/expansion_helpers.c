/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:50:00 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 18:16:14 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell.h"

int	handle_negative_zero(int *num, char *str, int *idx)
{
	if (*num < 0)
	{
		str[(*idx)++] = '-';
		*num = -(*num);
	}
	if (*num == 0)
	{
		str[(*idx)++] = '0';
		str[*idx] = '\0';
		return (1);
	}
	return (0);
}

void	convert_to_temp_buffer(int num, char *temp_buf, int *temp_idx)
{
	*temp_idx = 0;
	while (num > 0)
	{
		temp_buf[(*temp_idx)++] = '0' + (num % 10);
		num /= 10;
	}
}

void	reverse_temp_to_str(char *temp_buf, int temp_idx, char *str, int *idx)
{
	while (temp_idx > 0)
		str[(*idx)++] = temp_buf[--temp_idx];
	str[*idx] = '\0';
}

int	ft_process_char(const char *value, int *i, char **expanded)
{
	char	tmp[2];

	tmp[0] = value[(*i)++];
	tmp[1] = '\0';
	*expanded = ft_join_strings(*expanded, tmp, 0);
	if (*expanded != NULL)
		return (1);
	else
		return (0);
}

void	ft_itoa_simple(int num, char *str)
{
	int		idx;
	char	temp_buf[12];
	int		temp_idx;

	idx = 0;
	if (handle_negative_zero(&num, str, &idx))
		return ;
	convert_to_temp_buffer(num, temp_buf, &temp_idx);
	reverse_temp_to_str(temp_buf, temp_idx, str, &idx);
}
