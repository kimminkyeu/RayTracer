/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvector3__a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:08:58 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 12:09:38 by minkyeki         ###   ########.fr       */
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
