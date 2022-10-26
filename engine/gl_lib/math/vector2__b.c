/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2__b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:26:59 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 12:20:23 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_vec2.h"

t_vec2	gl_vec2_subtract_vector(t_vec2 v1, t_vec2 v2)
{
	return (gl_vec2_2f(v1.x - v2.x, v1.y - v2.y));
}

t_vec2	gl_vec2_multiply_scalar(t_vec2 v, float scalar)
{
	return (gl_vec2_2f(v.x * scalar, v.y * scalar));
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

t_vec2	gl_vec2_clamp(t_vec2 v, t_vec2 min, t_vec2 max)
{
	float	x;
	float	y;

	x = compare_for_clamp(v.x, min.x, max.x);
	y = compare_for_clamp(v.y, min.y, max.y);
	return (gl_vec2_2f(x, y));
}
