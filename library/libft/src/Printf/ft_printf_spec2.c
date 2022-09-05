/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_spec2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 22:40:13 by minkyeki          #+#    #+#             */
/*   Updated: 2022/05/01 20:47:22 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_spec_uint(va_list argp, t_print *_info)
{
	int	num;

	num = va_arg(argp, int);
	ft_putnbr_uint_fd((unsigned int)num, STDOUT);
	_info->print_cnt += ft_nbrlen_uint(num);
	_info->state = PRINTF_DONE;
}

void	handle_spec_lower_hex(va_list argp, t_print *_info)
{
	unsigned int	num;

	num = va_arg(argp, unsigned int);
	_info->print_cnt += (print_to_hex_fit((size_t)num, 0));
	_info->state = PRINTF_DONE;
}

void	handle_spec_upper_hex(va_list argp, t_print *_info)
{
	unsigned int	num;

	num = va_arg(argp, unsigned int);
	_info->print_cnt += (print_to_hex_fit((size_t)num, 1));
	_info->state = PRINTF_DONE;
}

int	get_spec_func_idx(const char *fmt)
{
	int			idx;
	const char	*specifier;

	specifier = "c%spdiuxX";
	idx = 0;
	while (specifier[idx] != '\0')
	{
		if (specifier[idx] == *fmt)
			return (idx);
		idx += 1;
	}
	return (10);
}

void	set_spec_func_table(void (*spec_func_table[])(va_list, t_print *))
{
	spec_func_table[0] = handle_spec_char;
	spec_func_table[1] = handle_spec_percent;
	spec_func_table[2] = handle_spec_str;
	spec_func_table[3] = handle_spec_addr;
	spec_func_table[4] = handle_spec_int;
	spec_func_table[5] = handle_spec_int;
	spec_func_table[6] = handle_spec_uint;
	spec_func_table[7] = handle_spec_lower_hex;
	spec_func_table[8] = handle_spec_upper_hex;
}
