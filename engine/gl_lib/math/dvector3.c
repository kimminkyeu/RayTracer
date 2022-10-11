/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvector3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:07:11 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/11 18:21:27 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_dvec3.h"

t_dvec3	gl_dvec3_3d(double _x, double _y, double _z)
{
	t_dvec3	pos3;

	pos3.x = _x;
	pos3.y = _y;
	pos3.z = _z;
	return (pos3);
}

t_dvec3	gl_dvec3_1d(double _k)
{
	return (gl_dvec3_3d(_k, _k, _k));
}

t_dvec3	gl_dvec3_reverse(t_dvec3 v)
{
	return (gl_dvec3_3d(-v.x, -v.y, -v.z));
}

t_dvec3	gl_dvec3_add_vector(t_dvec3 v1, t_dvec3 v2)
{
	return (gl_dvec3_3d(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_dvec3	gl_dvec3_add_double(t_dvec3 v, double f)
{
	return (gl_dvec3_3d(v.x + f, v.y + f, v.z + f));
}

t_dvec3	gl_dvec3_subtract_vector(t_dvec3 v1, t_dvec3 v2)
{
	return (gl_dvec3_3d(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_dvec3	gl_dvec3_multiply_scalar(t_dvec3 v, double scalar)
{
	return (gl_dvec3_3d(v.x * scalar, v.y * scalar, v.z * scalar));
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

t_dvec3	gl_dvec3_clamp(t_dvec3 v, t_dvec3 min, t_dvec3 max)
{
	double	x;
	double	y;
	double	z;

	x = compare_for_clamp(v.x, min.x, max.x);
	y = compare_for_clamp(v.y, min.y, max.y);
	z = compare_for_clamp(v.z, min.z, max.z);
	return (gl_dvec3_3d(x, y, z));
}

t_dvec3	gl_dvec3_normalize(t_dvec3 v)
{
	double	len;

	len = gl_dvec3_get_magnitude(v);
	return (gl_dvec3_3d(v.x / len, v.y / len, v.z / len));
}

double	gl_dvec3_dot(t_dvec3 dst, t_dvec3 src)
{
	return (dst.x * src.x + dst.y * src.y + dst.z * src.z);
}

double	gl_dvec3_get_magnitude(t_dvec3 v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

/** FIX: check if cross-product code is valid!  */
t_dvec3	gl_dvec3_cross(t_dvec3 v1, t_dvec3 v2)
{
	double	x;
	double	y;
	double	z;

	x = v1.y * v2.z - v1.z * v1.y;
	y = v1.z * v2.x - v1.x * v1.z;
	z = v1.x * v2.y - v1.y * v1.x;
	return (gl_dvec3_3d(x, y, z));
}
