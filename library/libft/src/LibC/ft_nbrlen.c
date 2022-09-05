/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 21:32:48 by minkyeki          #+#    #+#             */
/*   Updated: 2022/04/12 17:47:19 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_nbrlen(int num)
{
	size_t	len;
	size_t	sign;

	sign = 0;
	len = 0;
	if (num < 0)
		sign = 1;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= 10;
		len += 1;
	}
	return (len + sign);
}
