/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvector4__a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:11:34 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 12:11:58 by minkyeki         ###   ########.fr       */
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
