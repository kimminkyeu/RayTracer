/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvector3__b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:09:10 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 12:10:05 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_dvec3.h"

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
