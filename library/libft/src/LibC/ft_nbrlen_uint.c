/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 21:32:48 by minkyeki          #+#    #+#             */
/*   Updated: 2022/04/11 22:42:09 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_nbrlen_uint(unsigned int num_pos)
{
	size_t	len;

	len = 0;
	if (num_pos == 0)
		return (1);
	while (num_pos != 0)
	{
		num_pos /= 10;
		len += 1;
	}
	return (len);
}
