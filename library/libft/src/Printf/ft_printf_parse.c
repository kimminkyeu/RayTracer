/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:50:39 by minkyeki          #+#    #+#             */
/*   Updated: 2022/05/01 20:47:14 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_format(const char **fmt, va_list argp, t_print *_info)
{
	static void	(*spec_func_table[9])(va_list argp, t_print *_info);

	if (spec_func_table[8] == NULL)
		set_spec_func_table(spec_func_table);
	while (_info->state != PRINTF_DONE)
	{
		if (_info->state == PRINTF_FLAG)
			return ;
		else if (_info->state == PRINTF_WIDTH)
			return ;
		else if (_info->state == PRINTF_PRECISION)
			return ;
		else if (_info->state == PRINTF_LENGTH)
			return ;
		else if (_info->state == PRINTF_SPEC)
		{
			while (_info->state != PRINTF_DONE)
			{
				(spec_func_table[get_spec_func_idx(*fmt)])(argp, _info);
				(*fmt) += 1;
			}
		}
		else if (_info->state == PRINTF_ERROR)
			return ;
	}
}
