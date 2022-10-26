/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2__a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:26:59 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 12:20:06 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_vec2.h"

t_vec2	gl_vec2_2f(float _x, float _y)
{
	t_vec2	vec2;

	vec2.x = _x;
	vec2.y = _y;
	return (vec2);
}

t_vec2	gl_vec2_1f(float _k)
{
	return (gl_vec2_2f(_k, _k));
}

t_vec2	gl_vec2_reverse(t_vec2 v)
{
	return (gl_vec2_2f(-v.x, -v.y));
}

t_vec2	gl_vec2_add_vector(t_vec2 v1, t_vec2 v2)
{
	return (gl_vec2_2f(v1.x + v2.x, v1.y + v2.y));
}

t_vec2	gl_vec2_add_float(t_vec2 v1, float f)
{
	return (gl_vec2_2f(v1.x + f, v1.y + f));
}
