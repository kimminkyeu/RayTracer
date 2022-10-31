/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4__a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:15:46 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 12:16:12 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_vec4.h"

t_vec4	vec4_4f(float _x, float _y, float _z, float _w)
{
	t_vec4	pos4;

	pos4.x = _x;
	pos4.y = _y;
	pos4.z = _z;
	pos4.w = _w;
	return (pos4);
}

t_vec4	vec4_1f(float _k)
{
	return (vec4_4f(_k, _k, _k, _k));
}

t_vec4	vec4_reverse(t_vec4 v)
{
	return (vec4_4f(-v.x, -v.y, -v.z, -v.w));
}

t_vec4	add4(t_vec4 v1, t_vec4 v2)
{
	t_vec4	o;

	o = vec4_4f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
	return (o);
}

t_vec4	add4_f(t_vec4 v, float f)
{
	return (vec4_4f(v.x + f, v.y + f, v.z + f, v.w + f));
}
