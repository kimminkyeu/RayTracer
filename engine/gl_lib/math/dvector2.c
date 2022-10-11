/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvector2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:26:59 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/11 18:12:55 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_dvec2.h"

t_dvec2	gl_dvec2_2d(double _x, double _y)
{
	t_dvec2	vec2;

	vec2.x = _x;
	vec2.y = _y;
	return (vec2);
}

t_dvec2	gl_dvec2_1d(double _k)
{
	return (gl_dvec2_2d(_k, _k));
}

t_dvec2	gl_dvec2_reverse(t_dvec2 v)
{
	return (gl_dvec2_2d(-v.x, -v.y));
}

t_dvec2	gl_dvec2_add_vector(t_dvec2 v1, t_dvec2 v2)
{
	return (gl_dvec2_2d(v1.x + v2.x, v1.y + v2.y));
}

t_dvec2	gl_dvec2_add_double(t_dvec2 v1, double d)
{
	return (gl_dvec2_2d(v1.x + d, v1.y + d));
}

t_dvec2	gl_dvec2_subtract_vector(t_dvec2 v1, t_dvec2 v2)
{
	return (gl_dvec2_2d(v1.x - v2.x, v1.y - v2.y));
}

t_dvec2	gl_dvec2_multiply_scalar(t_dvec2 v, double scalar)
{
	return (gl_dvec2_2d(v.x * scalar, v.y * scalar));
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

t_dvec2	gl_dvec2_clamp(t_dvec2 v, t_dvec2 min, t_dvec2 max)
{
	double	x;
	double	y;

	x = compare_for_clamp(v.x, min.x, max.x);
	y = compare_for_clamp(v.y, min.y, max.y);
	return (gl_dvec2_2d(x, y));
}


double	gl_dvec2_dot(t_dvec2 v1, t_dvec2 v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

double	gl_dvec2_get_magnitude(t_dvec2 v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y)));
}

t_dvec2	gl_dvec2_normalize(t_dvec2 v)
{
	double	len;

	len = gl_vec2_get_magnitude(v);
	/** printf("len : %f\n", len); */
	return (gl_dvec2_2d(v.x / len, v.y / len));
}
