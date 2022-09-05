/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@42SEOUL.KR>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:29:31 by minkyeki          #+#    #+#             */
/*   Updated: 2022/04/12 14:48:21 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static unsigned int	get_base_size(char *base)
{
	int	size;

	size = 0;
	while (*base++)
		size++;
	return (size);
}

static long long	get_result_size(long long num, long long base_len)
{
	long long	size;

	size = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		num = -num;
	while (num != 0)
	{
		num /= base_len;
		++size;
	}
	return (size);
}

static void	init_out(char *out_arr, int num, long long num_len, char *base)
{
	int			sign;
	int			i;
	long long	base_len;
	long long	out_num;

	out_num = num;
	sign = 0;
	base_len = (long long)get_base_size(base);
	if (out_arr[0] == '-')
		sign = 1;
	if (out_num == 0)
	{
		out_arr[0] = base[0];
		out_arr[1] = '\0';
		return ;
	}
	i = 0;
	while (out_num != 0)
	{
		out_arr[num_len + (long long)sign - (long long)i - 1] \
			= base[(long long)out_num % base_len];
		out_num /= base_len;
		++i;
	}
	out_arr[num_len + (long long)sign] = '\0';
}

char	*ft_convert_nbr_base_malloc(int nb, char *base)
{
	long long	num_len;
	long long	base_len;
	long long	num;
	char		*out;
	int			sign;

	sign = 0;
	num = (long long)nb;
	if (nb < 0)
	{
		num *= -1;
		sign = 1;
	}
	base_len = get_base_size(base);
	num_len = get_result_size(num, base_len);
	out = malloc(sizeof(*out) * ((size_t)num_len + (size_t)sign + 1));
	if (!out)
		return (NULL);
	if (nb < 0)
		out[0] = '-';
	init_out(out, num, num_len, base);
	return (out);
}
