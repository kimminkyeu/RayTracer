/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3__c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:19:17 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 12:19:17 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_vec3.h"

t_vec3	gl_vec3_normalize(t_vec3 v)
{
	float	len;

	len = gl_vec3_get_magnitude(v);
	return (gl_vec3_3f(v.x / len, v.y / len, v.z / len));
}

float	gl_vec3_dot(t_vec3 dst, t_vec3 src)
{
	return (dst.x * src.x + dst.y * src.y + dst.z * src.z);
}

float	gl_vec3_get_magnitude(t_vec3 v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

t_vec3	gl_vec3_cross(t_vec3 v1, t_vec3 v2)
{
	float	x;
	float	y;
	float	z;

	x = v1.y * v2.z - v2.y * v1.z;
	y = v1.z * v2.x - v2.z * v1.x;
	z = v1.x * v2.y - v2.x * v1.y;
	return (gl_vec3_3f(x, y, z));
}
