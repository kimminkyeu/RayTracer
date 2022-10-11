/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 23:30:53 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/11 16:43:18 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_color.h"
#include "gl_draw.h"
#include "gl_vec4.h"
#include "gl_vec3.h"
#include "gl_vec2.h"
#include "libft.h"
#include "main.h"

// screen 좌표계를 world 좌표계로 변환. (-aspect ~ +aspect)
t_vec3 transform_screen_to_world(t_image *img, t_vec2 pos_screen)
{
	const float x_scale = 2.0f / img->img_size.width;
	const float y_scale = 2.0f / img->img_size.height;
	const float aspect_ratio = (float)img->img_size.width / img->img_size.height;

	// 3차원 공간으로 확장.
	return (gl_vec3_3f((pos_screen.x * x_scale - 1.0f) * aspect_ratio, -pos_screen.y * y_scale + 1.0f, 0.0f));
}

/* ----------------------------------------- *
 * |  NOTE:  Main Ray-tracing Algorithm !    |
 ------------------------------------------- */
t_vec3 trace_ray(t_device *device, t_ray *ray)
{
	if (device->objects.spheres->size == 0)
		return (gl_vec3_1f(0.0f));

	// NOTE:  Test code for ray_tracing (현재는 Sphere 하나만 추적 중)
	t_sphere *sphere = device->objects.spheres->data[0];
	t_hit hit = sphere_intersect_ray_collision(ray, sphere);

	if (hit.distance < 0.0f) // if no hit.
	{
		return (gl_vec3_3f(0.0f, 0.0f, 0.0f)); // return black
	}
	else // if ray hit object.
	{
		// NOTE:  Diffuse
		const t_vec3 hit_point_to_light = gl_vec3_normalize(gl_vec3_subtract_vector(device->light->pos, hit.point));
		const float _diff = maxf(gl_vec3_dot(hit.normal, hit_point_to_light), 0.0f);
		// (void)_diff;
		// Test code for diffuse
		// return (gl_vec3_multiply_scalar(sphere->diffuse, _diff));

		// NOTE:  Specular [ 2 * (N . L)N - L ]
		const t_vec3 reflection_dir = gl_vec3_subtract_vector(gl_vec3_multiply_scalar(gl_vec3_multiply_scalar(hit.normal, gl_vec3_dot(hit_point_to_light, hit.normal)), 2.0f), hit_point_to_light);
		const float _spec = pow(maxf(gl_vec3_dot(gl_vec3_reverse(ray->direction), reflection_dir), 0.0f), sphere->alpha);
		// return (gl_vec3_multiply_scalar(gl_vec3_multiply_scalar(sphere->specular, _spec), sphere->ks));

		// Phong Reflection Model 최종합.
		const t_vec3 diffuse_final = gl_vec3_multiply_scalar(sphere->diffuse, _diff);
		const t_vec3 specular_final = gl_vec3_multiply_scalar(gl_vec3_multiply_scalar(sphere->specular, _spec), sphere->ks);
		const t_vec3 phong_reflection = gl_vec3_add_vector(gl_vec3_add_vector(sphere->ambient, diffuse_final), specular_final);
		return (phong_reflection);
	}
}

int	update(t_device *device, t_image *img)
{
	// ray_tracing
	int	x = 0;
	int y = 0;

	while (y < img->img_size.height)
	{
		x = 0;
		while (x < img->img_size.width)
		{
			const t_vec3 pixel_pos_world = transform_screen_to_world(img, gl_vec2_2f(x, y));

			// ray 방향 벡터. 현재 코드는 등각투시. (ray가 방향이 모두 같음. 추후 변경 필요)
			const t_vec3 ray_dir = gl_vec3_3f(0.0f, 0.0f, 1.0f);

			t_ray pixel_ray = create_ray(pixel_pos_world, ray_dir);
			t_vec3 tmp = gl_vec3_clamp(trace_ray(device, &pixel_ray), gl_vec3_1f(0.0f), gl_vec3_1f(255.0f));

			int final_color = gl_get_color_from_vec4(gl_vec4_4f(tmp.b, tmp.g, tmp.r, 0.0f));
			gl_draw_pixel(img, x, y, final_color);

			x++;
		}
		y++;
	}


	return (0);
}
