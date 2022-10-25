/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:34:01 by sungjpar          #+#    #+#             */
/*   Updated: 2022/10/22 14:34:09 by sungjpar         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_sign(const char c)
{
	if (c == '-')
		return (-1);
	else
		return (1);
}

float	ft_atof(const char *str)
{
	int		sign;
	float	result;
	float	pow;

	sign = get_sign(*str);
	str += (*str == '+' || *str == '-');
	result = 0;
	while (*str && ft_isdigit(*str))
	{
		result = result * 10 + (float)(*str - '0');
		++str;
	}
	if (*str != '.')
		return (result * sign);
	pow = 0.1f;
	++str;
	while (*str && ft_isdigit(*str))
	{
		result = result + (((float)(*str - '0')) * pow);
		pow *= 0.1f;
		++str;
	}
	return (result * sign);
}
