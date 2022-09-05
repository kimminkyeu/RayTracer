/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 22:46:46 by minkyeki          #+#    #+#             */
/*   Updated: 2022/05/01 20:47:09 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

t_print	*init_info_malloc(void)
{
	t_print	*pa_info;

	pa_info = malloc(sizeof(*pa_info));
	pa_info->state = PRINTF_NORMAL;
	pa_info->print_cnt = 0;
	return (pa_info);
}

void	reset_state(t_print *_info)
{
	_info->state = PRINTF_NORMAL;
}
