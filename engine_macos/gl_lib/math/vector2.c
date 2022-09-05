/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:26:59 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/05 19:51:11 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_vec2.h"

t_vec2	gl_vec2(float _x, float _y)
{
	t_vec2	vec2;

	vec2.x = _x;
	vec2.y = _y;
	return (vec2);
}

float	gl_vec2_dot_product(t_vec2 v1, t_vec2 v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

float	gl_vec2_get_magnitude(t_vec2 v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y)));
}

/** #include <stdio.h> */

t_vec2	gl_vec2_normalize(t_vec2 v)
{
	float	len;
	
	len = gl_vec2_get_magnitude(v);
	/** printf("len : %f\n", len); */
	return (gl_vec2(v.x / len, v.y / len));
}
