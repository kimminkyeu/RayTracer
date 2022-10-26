/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvector2__b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:26:59 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 12:07:04 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_dvec2.h"

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
