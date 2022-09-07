/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:07:11 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/07 13:29:57 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_vec4.h"

t_vec4	gl_vec4(float _x, float _y, float _z, float _w)
{
	t_vec4	pos4;

	pos4.x = _x;
	pos4.y = _y;
	pos4.z = _z;
	pos4.w = _w;
	return (pos4);
}

t_vec4	gl_vec4_normalize(t_vec4 v)
{
	float	len;

	len = gl_vec4_get_magnitude(v);
	return (gl_vec4(v.x / len, v.y / len, v.z / len, v.w));
}

float	gl_vec4_dot_product(t_vec4 dst, t_vec4 src)
{
	return (dst.x * src.x + dst.y * src.y + dst.z * src.z + dst.w * src.w);
}

float	gl_vec4_get_magnitude(t_vec4 v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w)));
}

/** FIX: check if cross-product code is valid!  */
t_vec4	gl_vec4_cross_product(t_vec4 v1, t_vec4 v2)
{
	float	x;
	float	y;
	float	z;

	x = v1.y * v2.z - v1.z * v1.y;
	y = v1.z * v2.x - v1.x * v1.z;
	z = v1.x * v2.y - v1.y * v1.x;
	return (gl_vec4(x, y, z, 1.0f));
}

/** NOTE : because float 0.0f is not exactly 0, use epsilon. */
t_vec4	gl_vec4_multiply_matrix(t_mat4x4 m, t_vec4 v)
{
	t_vec4	o;
	float	epsilon;

	epsilon = 0.00001f;
	o.x = v.x * m.m[0][0] + v.y * m.m[0][1] + v.z * \
		m.m[0][2] + v.w * m.m[0][3];
	o.y = v.x * m.m[1][0] + v.y * m.m[1][1] + v.z * \
		m.m[1][2] + v.w * m.m[1][3];
	o.z = v.x * m.m[2][0] + v.y * m.m[2][1] + v.z * \
		m.m[2][2] + v.w * m.m[2][3];
	o.w = v.x * m.m[3][0] + v.y * m.m[3][1] + v.z * \
		m.m[3][2] + v.w * m.m[3][3];
	if (!(o.w < epsilon && o.w > -epsilon) \
			&& !(o.w < 1.0f + epsilon && o.w > 1.0f - epsilon))
	{
		o.x /= o.w;
		o.y /= o.w;
		o.z /= o.w;
	}
	return (gl_vec4(o.x, o.y, o.z, 1.0f));
}
