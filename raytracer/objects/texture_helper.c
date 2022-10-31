/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:06:31 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/31 17:35:58 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // usleep
#include "gl_color.h"
#include "gl_draw.h"
#include "gl_vec2.h"
#include "gl_vec3.h"
#include "texture.h"
#include "main.h"

t_vec3	get_clamped(t_texture *texture, int i, int j)
{
	t_vec4	point;
	float	r;
	float	g;
	float	b;

	i = clamp_int(i, 0, texture->width - 1);
	j = clamp_int(j, 0, texture->height - 1);
	point = gl_get_pixel_color_vec4(&texture->image, i, j);
	r = point.r / 255.0f;
	g = point.g / 255.0f;
	b = point.b / 255.0f;
	return (vec3_3f(b, g, r));
}

t_vec3	get_clamped_raw(t_texture *texture, int i, int j)
{
	t_vec4	point;
	float	r;
	float	g;
	float	b;

	i = clamp_int(i, 0, texture->width - 1);
	j = clamp_int(j, 0, texture->height - 1);
	point = gl_get_pixel_color_vec4(&texture->image, i, j);
	r = point.r;
	g = point.g;
	b = point.b;
	return (vec3_3f(b, g, r));
}

t_vec3	get_wrapped(t_texture *texture, int i, int j)
{
	t_vec4	point;
	float	r;
	float	g;
	float	b;

	i %= texture->width;
	j %= texture->height;
	if (i < 0)
		i += texture->width;
	if (j < 0)
		j += texture->height;
	point = gl_get_pixel_color_vec4(&texture->image, i, j);
	r = point.r / 255.0f;
	g = point.g / 255.0f;
	b = point.b / 255.0f;
	return (vec3_3f(b, g, r));
}

t_vec3	get_wrapped_raw(t_texture *texture, int i, int j)
{
	t_vec4	point;
	float	r;
	float	g;
	float	b;

	i %= texture->width;
	j %= texture->height;
	if (i < 0)
		i += texture->width;
	if (j < 0)
		j += texture->height;
	point = gl_get_pixel_color_vec4(&texture->image, i, j);
	r = point.r;
	g = point.g;
	b = point.b;
	return (vec3_3f(b, g, r));
}
