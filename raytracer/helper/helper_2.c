/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:43:34 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/28 19:38:15 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "objects.h"
#include "texture.h"
#include "gl_engine.h"

float	get_area(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	cross;

	cross = cross3(vec1, vec2);
	return (len3(cross) * 0.5f);
}

t_vec3	get_barycentric_coord(t_vec3 v0, t_vec3 v1, t_vec3 v2, t_vec3 point)
{
	const float		area0 = get_area(sub3(point, v2), \
                                        sub3(v1, v2));
	const float		area1 = get_area(sub3(point, v0), \
                                        sub3(v2, v0));
	const float		area2 = get_area(sub3(v1, v0), \
                                        sub3(point, v0));
	const float		w0 = area0 / (area0 + area1 + area2);
	const float		w1 = area1 / (area0 + area1 + area2);

	return (vec3_3f(w0, w1, 1.0f - w0 - w1));
}

/** helper function. (min) */
float	min_float(float f1, float f2)
{
	if (f1 >= f2)
		return (f2);
	else
		return (f1);
}

/** helper function. (max) */
float	max_float(float f1, float f2)
{
	if (f1 >= f2)
		return (f1);
	else
		return (f2);
}

/** helper function. (abs) */
float	abs_float(float f)
{
	if (f >= 0.0f)
		return (f);
	else
		return (-f);
}
