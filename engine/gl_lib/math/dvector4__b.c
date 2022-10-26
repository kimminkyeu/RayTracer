/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvector4__b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:11:42 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 12:14:33 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_dvec4.h"

t_dvec4	gl_dvec4_subtract_vector(t_dvec4 v1, t_dvec4 v2)
{
	return (gl_dvec4_4d(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w));
}

t_dvec4	gl_dvec4_multiply_scalar(t_dvec4 v, double scalar)
{
	return (gl_dvec4_4d(v.x * scalar, v.y * scalar, v.z \
						* scalar, v.w * scalar));
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
