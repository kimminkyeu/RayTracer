/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3__b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:19:12 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/30 21:32:25 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_vec3.h"

t_vec3	gl_vec3_subtract_vector(t_vec3 v1, t_vec3 v2)
{
	return (gl_vec3_3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vec3	gl_vec3_multiply_scalar(t_vec3 v, float scalar)
{
	return (gl_vec3_3f(v.x * scalar, v.y * scalar, v.z * scalar));
}

t_vec3 gl_vec3_multiply_vector(t_vec3 v1,t_vec3 v2)
{
	return (gl_vec3_3f(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z));
}

/** helper function for gl_clamp */
static float	compare_for_clamp(float x, float min_val, float max_val)
{
	if (x > max_val)
		return (max_val);
	else if (x < min_val)
		return (min_val);
	else
		return (x);
}

t_vec3	gl_vec3_clamp(t_vec3 v, t_vec3 min, t_vec3 max)
{
	float	x;
	float	y;
	float	z;

	x = compare_for_clamp(v.x, min.x, max.x);
	y = compare_for_clamp(v.y, min.y, max.y);
	z = compare_for_clamp(v.z, min.z, max.z);
	return (gl_vec3_3f(x, y, z));
}
