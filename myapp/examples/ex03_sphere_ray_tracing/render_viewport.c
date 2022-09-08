/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_viewport.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 23:30:53 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/08 21:28:27 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/** TODO: change to 
 * gl_color_from_vec4(const t_vec4 vec) */
int	convert_to_rgba(const t_vec4 color)
{
	/** TODO: add vec4 to color type. vec4.r, vec4.g, vec4.b, vec4.a */
	int r = (int)(color.r * 255.0f);
	int g = (int)(color.g * 255.0f);
	int b = (int)(color.b * 255.0f);
	int a = (int)(color.a * 255.0f);

	return (gl_color(a, r, g, b));
}

/** NOTE: Main Shader function */
t_vec4	per_pixel(t_vec2 coord)
{
	// (1) Change 
	// Sphere Formula
	// (bx^2 + by^2)t^2 + (2(axbx + ayby))t + (ax^2 + ay^2 - r^2) = 0
	// where
	// a = ray origin
	// b = ray direction
	// r = radius
	// t = hit distance
	t_vec3 ray_origin = gl_vec3(0.0f, 0.0f, 1.0f);
	t_vec3 ray_direction = gl_vec3(coord.x, coord.y, -1.0f);
	/** ray_direction = gl_vec3_normalize(ray_direction); */

	float radius = 0.5f;
		
	// Quodratic formula discriminant
	// t = b^2 - 4ac
	float a = gl_vec3_dot_product(ray_direction, ray_direction);
	float b = 2.0f * gl_vec3_dot_product(ray_origin, ray_direction);
	float c = gl_vec3_dot_product(ray_origin, ray_origin) - radius * radius;

	float discriminant = b * b - 4.0f * a * c;

	// if is outside circle
	if (discriminant < 0.0f)
		return (gl_vec4(0, 0, 0, 1));

	/** 구에 접하는 두점. 안쪽과 바깥쪽 */
	float closest_t = (-b - sqrtf(discriminant)) / (2.0f * a);

	t_vec3 hit_point = gl_vec3_add_vector(ray_origin, gl_vec3_multiply_scalar(ray_direction, closest_t));
	t_vec3 normal = gl_vec3_normalize(hit_point);

	t_vec3 light_dir = gl_vec3_normalize(gl_vec3(-1, -1, -1));
	t_vec3 negative_light_dir = gl_vec3_reverse(light_dir);

	float d = fmaxf(gl_vec3_dot_product(normal, negative_light_dir), 0.0f);

	t_vec3 sphereColor = gl_vec3(1, 0, 1);

	sphereColor = gl_vec3_multiply_scalar(sphereColor, d);
	// sphereColor.x *= d;
	// sphereColor.y *= d;
	// sphereColor.z *= d;

	return (gl_vec4(sphereColor.x, sphereColor.y, sphereColor.z, 0.0f));
}

int	render_viewport(t_device *device, t_image *viewport)
{		
	/** WARN: Use Static Variable for private data member! */
	(void)device;

	int	x;
	int	y;
	t_vec2	coord;

	/** (1) Basic While-loop for Ray */
	y = 0;
	while (y < viewport->height)
	{
		x = 0;
		while (x < viewport->width)
		{
			// coord from (0.0f ~ 1.0f)
			coord = gl_vec2((float)x / (float)viewport->width, (float)y / (float)viewport->height);

			// Change coord value to (-1.0f ~ 1.0f)
			coord.x = coord.x * 2.0f - 1.0f;
			coord.y = coord.y * 2.0f - 1.0f;
			t_vec4 color = per_pixel(coord);
			color = gl_vec4_clamp(color, gl_vec4(0.0f, 0.0f, 0.0f, 0.0f), gl_vec4(1.0f, 1.0f, 1.0f, 1.0f));

			/** TODO: make gl_clamp(t_vec4 color, float min, float max) --> 최소 최댓값 변경. 
			 * https://github.com/g-truc/glm --> gml library */
			gl_draw_pixel(viewport, x, y, convert_to_rgba(color));
			x++;
		}
		y++;
	}
	return (0);
}