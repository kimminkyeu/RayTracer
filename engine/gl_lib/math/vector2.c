/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:26:59 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/08 19:37:31 by minkyeki         ###   ########.fr       */
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

extern t_vec2	gl_vec2_reverse(t_vec2 v)
{
	return (gl_vec2(-v.x, -v.y));
}

extern t_vec2	gl_vec2_add(t_vec2 v1, t_vec2 v2)
{
	return (gl_vec2(v1.x + v2.x, v1.y + v2.y));
}

extern t_vec2	gl_vec2_subtract(t_vec2 v1, t_vec2 v2)
{
	return (gl_vec2(v1.x - v2.x, v1.y - v2.y));
}

/** helper function for gl_clamp */
static float	compare_for_clamp(float x, float min_val, float max_val)
{
	if (x > max_val)
		return (max_val);
	else if (x < min_val)
		return (min_val);
	else
		return (x);
}

extern t_vec2	gl_vec2_clamp(t_vec2 v, t_vec2 min, t_vec2 max)
{
	float	x;
	float	y;

	x = compare_for_clamp(v.x, min.x, max.x);
	y = compare_for_clamp(v.y, min.y, max.y);
	return (gl_vec2(x, y));
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
