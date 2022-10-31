/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:06:31 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/31 01:53:16 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // usleep
#include "gl_color.h"
#include "gl_draw.h"
#include "gl_vec2.h"
#include "gl_vec3.h"
#include "texture.h"
#include "main.h"

static void fill_checker_board(t_texture *texture)
{
	int x = 0;
	int y = 0;

	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{
			if (x % 2 == y % 2)
				gl_draw_pixel(&texture->image, x, y, BLACK);
			else
				gl_draw_pixel(&texture->image, x, y, WHITE);
			x++;
		}
		y++;
	}
}

t_texture	*new_texture_checkerboard(t_device *device, int width, int height)
{
	t_texture	*texture;

	texture = ft_calloc(1, sizeof(*texture));
	if (device == NULL || texture == NULL)
		return (NULL);
	texture->image.img_ptr = mlx_new_image(device->mlx, width, height);
	texture->image.mlx_ptr = device->mlx;
	if (texture->image.img_ptr == NULL)
	{
		free(texture);
		return (NULL);
	}
	texture->type = TEXTURE_CHECKER;
	texture->width = width;
	texture->image.img_size.width = width;
	texture->height = height;
	texture->image.img_size.height = height;
	texture->image.addr
		= mlx_get_data_addr(texture->image.img_ptr,
			&(texture->image.bits_per_pixel),
			&(texture->image.line_length), &(texture->image.endian));
	fill_checker_board(texture);
	return (texture);
}

void	init_texture(t_texture *texture, int width, int height)
{
	texture->width = width;
	texture->image.img_size.width = width;
	texture->height = height;
	texture->image.img_size.height = height;
	texture->image.addr = mlx_get_data_addr(texture->image.img_ptr, \
				&(texture->image.bits_per_pixel), \
				&(texture->image.line_length), &(texture->image.endian));
}

t_texture	*new_texture(t_device *device, char* filename)
{
	t_texture	*texture;
	char		*filename_without_newline;
	int			width;
	int			height;

	texture = ft_calloc(1, sizeof(*texture));
	if (device == NULL || filename == NULL || texture == NULL)
		return (NULL);
	texture->type = TEXTURE_FILE;
	filename_without_newline = ft_strtrim(filename, "\n");
	texture->image.img_ptr
		= mlx_xpm_file_to_image(device->mlx,
			filename_without_newline, &width, &height);
	texture->image.mlx_ptr = device->mlx;
	free(filename_without_newline);
	if (texture->image.img_ptr == NULL)
	{
		printf("Error while loading texture [%s]\n", filename);
		free(texture);
		return (NULL);
	}
	init_texture(texture, width, height);
	return (texture);
}

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

t_vec3 sample_point(t_texture *texture, const t_vec2 uv, int is_raw)
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

typedef struct s_p4
{
	t_vec3 c00;
	t_vec3 c01;
	t_vec3 c10;
	t_vec3 c11;
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

t_vec3 sample_linear(t_texture *texture, const t_vec2 uv, int is_raw)
{
	t_vec2	xy;
	float	i;
	float	j;
	float	dx;
	float	dy;

	(void)uv; (void)texture;
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
	const t_vec3	rgb = sample_point(hit->obj->normal_texture, hit->uv, false);
	t_vec3			derivative;
	t_vec3			bitangent_result;
	t_vec3			normal_result;
	t_vec3			final_normal;

	derivative.r = (rgb.r - 0.5f) * 2.0f;
	derivative.g = (rgb.g - 0.5f) * 2.0f;
	derivative.b = (rgb.b - 0.5f) * 2.0f;
	bitangent_result
		= mult3_scalar(cross3(hit->normal, hit->tangent),derivative.x);
	normal_result = mult3_scalar(hit->normal, derivative.z);
	final_normal = add3(normal_result, mult3_scalar(hit->tangent, derivative.y));
	final_normal = add3(final_normal, bitangent_result);
	final_normal = normal3(add3(final_normal, bitangent_result));
	return (final_normal);
}
