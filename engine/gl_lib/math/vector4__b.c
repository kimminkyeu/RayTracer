/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4__b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:15:52 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 12:17:09 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_vec4.h"

t_vec4	gl_vec4_subtract_vector(t_vec4 v1, t_vec4 v2)
{
	return (gl_vec4_4f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w));
}

t_vec4	gl_vec4_multiply_scalar(t_vec4 v, float scalar)
{
	return (gl_vec4_4f(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar));
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

extern t_vec4	gl_vec4_clamp(t_vec4 v, t_vec4 min, t_vec4 max)
{
	float	x;
	float	y;
	float	z;
	float	w;

	x = compare_for_clamp(v.x, min.x, max.x);
	y = compare_for_clamp(v.y, min.y, max.y);
	z = compare_for_clamp(v.z, min.z, max.z);
	w = compare_for_clamp(v.w, min.w, max.w);
	return (gl_vec4_4f(x, y, z, w));
}
