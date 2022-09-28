/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:07:11 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/14 22:34:08 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_vec3.h"

t_vec3	gl_vec3_3f(float _x, float _y, float _z)
{
	t_vec3	pos3;

	pos3.x = _x;
	pos3.y = _y;
	pos3.z = _z;
	return (pos3);
}

t_vec3	gl_vec3_1f(float _k)
{
	return (gl_vec3_3f(_k, _k, _k));
}

t_vec3	gl_vec3_reverse(t_vec3 v)
{
	return (gl_vec3_3f(-v.x, -v.y, -v.z));
}

t_vec3	gl_vec3_add_vector(t_vec3 v1, t_vec3 v2)
{
	return (gl_vec3_3f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vec3	gl_vec3_add_float(t_vec3 v, float f)
{
	return (gl_vec3_3f(v.x + f, v.y + f, v.z + f));
}

t_vec3	gl_vec3_subtract_vector(t_vec3 v1, t_vec3 v2)
{
	return (gl_vec3_3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vec3	gl_vec3_multiply_scalar(t_vec3 v, float scalar)
{
	return (gl_vec3_3f(v.x * scalar, v.y * scalar, v.z * scalar));
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

t_vec3	gl_vec3_clamp(t_vec3 v, t_vec3 min, t_vec3 max)
{
	float	x;
	float	y;
	float	z;

	x = compare_for_clamp(v.x, min.x, max.x);
	y = compare_for_clamp(v.y, min.y, max.y);
	z = compare_for_clamp(v.z, min.z, max.z);
	return (gl_vec3_3f(x, y, z));
}

t_vec3	gl_vec3_normalize(t_vec3 v)
{
	float	len;

	len = gl_vec3_get_magnitude(v);
	return (gl_vec3_3f(v.x / len, v.y / len, v.z / len));
}

float	gl_vec3_dot_product(t_vec3 dst, t_vec3 src)
{
	return (dst.x * src.x + dst.y * src.y + dst.z * src.z);
}

float	gl_vec3_get_magnitude(t_vec3 v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

/** FIX: check if cross-product code is valid!  */
t_vec3	gl_vec3_cross_product(t_vec3 v1, t_vec3 v2)
{
	float	x;
	float	y;
	float	z;

	x = v1.y * v2.z - v1.z * v1.y;
	y = v1.z * v2.x - v1.x * v1.z;
	z = v1.x * v2.y - v1.y * v1.x;
	return (gl_vec3_3f(x, y, z));
}
