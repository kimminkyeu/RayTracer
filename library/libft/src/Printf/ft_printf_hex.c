/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 20:56:23 by minkyeki          #+#    #+#             */
/*   Updated: 2022/05/01 20:47:05 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static size_t	get_result_size(size_t num, size_t base_len)
{
	size_t	size;

	size = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= base_len;
		++size;
	}
	return (size);
}

void	print_to_hex_16(size_t nb, int mode)
{
	size_t			_8byte;
	char			output[17];
	size_t			count;
	const char		*hex;

	if (mode == 0)
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	count = 16;
	_8byte = (size_t)nb;
	while (count > 0)
	{
		output[count - 1] = hex[(_8byte % 16)];
		_8byte = _8byte / 16;
		--count;
	}
	output[16] = '\0';
	ft_putstr_fd(output, STDOUT);
}

size_t	print_to_hex_fit(size_t nb, int mode)
{
	char			*output;
	size_t			len;
	size_t			len_cpy;
	const char		*hex;

	if (mode == 0)
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	len = get_result_size(nb, 16);
	len_cpy = len;
	output = malloc(sizeof(*output) * (len + 1));
	output[len] = '\0';
	while (len > 0)
	{
		output[len - 1] = hex[(nb % 16)];
		nb = nb / 16;
		len -= 1;
	}
	ft_putstr_fd(output, STDOUT);
	free(output);
	return (len_cpy);
}

size_t	print_to_hex_len(size_t nb, size_t n, int mode)
{
	char			*output;
	size_t			len;
	size_t			result_len;
	const char		*hex;

	if (mode == 0)
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	len = get_result_size(nb, 16);
	if (n > len)
		n = len;
	result_len = n;
	output = malloc(sizeof(*output) * (n + 1));
	output[n] = '\0';
	while (n > 0)
	{
		output[n - 1] = hex[(nb % 16)];
		nb = nb / 16;
		n -= 1;
	}
	ft_putstr_fd(output, STDOUT);
	free(output);
	return (result_len);
}
