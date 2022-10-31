/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3__a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:18:14 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 12:18:29 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_vec3.h"

t_vec3	vec3_3f(float _x, float _y, float _z)
{
	t_vec3	pos3;

	pos3.x = _x;
	pos3.y = _y;
	pos3.z = _z;
	return (pos3);
}

t_vec3	vec3_1f(float _k)
{
	return (vec3_3f(_k, _k, _k));
}

t_vec3	vec3_reverse(t_vec3 v)
{
	return (vec3_3f(-v.x, -v.y, -v.z));
}

t_vec3	add3(t_vec3 v1, t_vec3 v2)
{
	return (vec3_3f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vec3	add3_f(t_vec3 v, float f)
{
	return (vec3_3f(v.x + f, v.y + f, v.z + f));
}
