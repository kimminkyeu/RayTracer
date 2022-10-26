/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvector3__c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:09:17 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 12:10:27 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_dvec3.h"

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

	x = v1.y * v2.z - v2.y * v1.z;
	y = v1.z * v2.x - v2.z * v1.x;
	z = v1.x * v2.y - v2.x * v1.y;
	return (gl_dvec3_3d(x, y, z));
}
