/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:06:31 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/31 17:56:38 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // usleep
#include "gl_color.h"
#include "gl_draw.h"
#include "gl_vec2.h"
#include "gl_vec3.h"
#include "texture.h"
#include "main.h"

typedef struct s_p4
{
	t_vec3	c00;
	t_vec3	c01;
	t_vec3	c10;
	t_vec3	c11;
}	t_p4;

t_p4	p4(t_vec3 c00, t_vec3 c01, t_vec3 c10, t_vec3 c11)
{
	const t_p4	result = {
		c00, c01, c10, c11
	};

	return (result);
}

t_vec3	interpolate_bilinear(
		const float dx,
		const float dy,
		const t_p4 p4)
{
	const t_vec3	color_x0
		= add3(mult3_scalar(p4.c00, 1.0f - dx), mult3_scalar(p4.c10, dx));
	const t_vec3	color_x1
		= add3(mult3_scalar(p4.c01, 1.0f - dx), mult3_scalar(p4.c11, dx));
	const t_vec3	color_y
		= add3(mult3_scalar(color_x0, 1.0f - dy), mult3_scalar(color_x1, dy));

	return (color_y);
}

t_vec3	sample_linear(t_texture *texture, const t_vec2 uv, int is_raw)
{
	t_vec2	xy;
	float	i;
	float	j;
	float	dx;
	float	dy;

	xy = vec2_2f(uv.x * (float) texture->width, uv.y * (float) texture->height);
	xy = add2_f(xy, -0.5f);
	i = (int)floor(xy.x);
	j = (int)floor(xy.y);
	dx = (float)xy.x - (float)i;
	dy = (float)xy.y - (float)j;
	if (is_raw != true)
		return (
			interpolate_bilinear(dx, dy,
				p4(get_wrapped(texture, i, j), get_wrapped(texture, i + 1, j),
					get_wrapped(texture, i, j + 1),
					get_wrapped(texture, i + 1, j + 1))));
	else
		return (interpolate_bilinear(dx, dy,
				p4(get_wrapped_raw(texture, i, j),
					get_wrapped_raw(texture, i + 1, j),
					get_wrapped_raw(texture, i, j + 1),
					get_wrapped_raw(texture, i + 1, j + 1))));
}

t_vec3	sample_normal_map(const t_hit *hit)
{
	const t_vec3	rgb = sample_point(hit->obj->normal_texture, \
		hit->uv, false);
	t_vec3			derivative;
	t_vec3			bitangent_result;
	t_vec3			normal_result;
	t_vec3			final_normal;

	derivative.r = (rgb.r - 0.5f) * 2.0f;
	derivative.g = (rgb.g - 0.5f) * 2.0f;
	derivative.b = (rgb.b - 0.5f) * 2.0f;
	bitangent_result = \
		mult3_scalar(cross3(hit->normal, hit->tangent), derivative.x);
	normal_result = mult3_scalar(hit->normal, derivative.z);
	final_normal = add3(normal_result, \
		mult3_scalar(hit->tangent, derivative.y));
	final_normal = add3(final_normal, bitangent_result);
	final_normal = normal3(add3(final_normal, bitangent_result));
	return (final_normal);
}

t_vec3	sample_point(t_texture *texture, const t_vec2 uv, int is_raw)
{
	t_vec2	xy;
	int		i;
	int		j;

	(void)uv;
	(void)texture;
	xy = vec2_2f(uv.x * (float) texture->width, uv.y * (float) texture->height);
	xy = add2_f(xy, -0.5f);
	i = (int)round(xy.x);
	j = (int)round(xy.y);
	if (is_raw != true)
		return (get_clamped(texture, i, j));
	else
		return (get_clamped_raw(texture, i, j));
}
