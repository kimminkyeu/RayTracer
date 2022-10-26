/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvector4__c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:11:47 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 12:12:46 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_dvec4.h"

t_dvec4	gl_dvec4_normalize(t_dvec4 v)
{
	double	len;

	len = gl_dvec4_get_magnitude(v);
	return (gl_dvec4_4d(v.x / len, v.y / len, v.z / len, v.w));
}

double	gl_dvec4_dot(t_dvec4 dst, t_dvec4 src)
{
	return (dst.x * src.x + dst.y * src.y + dst.z * src.z + dst.w * src.w);
}

double	gl_dvec4_get_magnitude(t_dvec4 v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w)));
}

/** FIX: check if cross-product code is valid!  */
t_dvec4	gl_dvec4_cross(t_dvec4 v1, t_dvec4 v2)
{
	double	x;
	double	y;
	double	z;

	x = v1.y * v2.z - v2.y * v1.z;
	y = v1.z * v2.x - v2.z * v1.x;
	z = v1.x * v2.y - v2.x * v1.y;
	return (gl_dvec4_4d(x, y, z, 1.0f));
}

/** NOTE : because double 0.0f is not exactly 0, use epsilon. */
t_dvec4	gl_dvec4_multiply_matrix(t_mat4x4 m, t_dvec4 v)
{
	t_dvec4	o;
	double	epsilon;

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
	return (gl_dvec4_4d(o.x, o.y, o.z, 1.0f));
}
