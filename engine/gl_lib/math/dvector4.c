/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvector4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:07:11 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/11 19:33:28 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_dvec4.h"

t_dvec4	gl_dvec4_4d(double _x, double _y, double _z, double _w)
{
	t_dvec4	pos4;

	pos4.x = _x;
	pos4.y = _y;
	pos4.z = _z;
	pos4.w = _w;
	return (pos4);
}

t_dvec4	gl_dvec4_1d(double _k)
{
	return (gl_dvec4_4d(_k, _k, _k, _k));
}

t_dvec4	gl_dvec4_reverse(t_dvec4 v)
{
	return (gl_dvec4_4d(-v.x, -v.y, -v.z, -v.w));
}

t_dvec4	gl_dvec4_add_vector(t_dvec4 v1, t_dvec4 v2)
{
	t_dvec4	o;

	o = gl_dvec4_4d(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
	return (o);
}

t_dvec4	gl_dvec4_add_double(t_dvec4 v, double f)
{
	return (gl_dvec4_4d(v.x + f, v.y + f, v.z + f, v.w + f));
}

t_dvec4	gl_dvec4_subtract_vector(t_dvec4 v1, t_dvec4 v2)
{
	return (gl_dvec4_4d(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w));
}

t_dvec4	gl_dvec4_multiply_scalar(t_dvec4 v, double scalar)
{
	return (gl_dvec4_4d(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar));
}

/** helper function for gl_clamp */
static double	compare_for_clamp(double x, double min_val, double max_val)
{
	if (x > max_val)
		return (max_val);
	else if (x < min_val)
		return (min_val);
	else
		return (x);
}

extern t_dvec4	gl_dvec4_clamp(t_dvec4 v, t_dvec4 min, t_dvec4 max)
{
	double	x;
	double	y;
	double	z;
	double	w;

	x = compare_for_clamp(v.x, min.x, max.x);
	y = compare_for_clamp(v.y, min.y, max.y);
	z = compare_for_clamp(v.z, min.z, max.z);
	w = compare_for_clamp(v.w, min.w, max.w);
	return (gl_dvec4_4d(x, y, z, w));
}

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

	x = v1.y * v2.z - v1.z * v1.y;
	y = v1.z * v2.x - v1.x * v1.z;
	z = v1.x * v2.y - v1.y * v1.x;
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
