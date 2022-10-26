/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvector2__a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:05:41 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 12:05:51 by minkyeki         ###   ########.fr       */
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
