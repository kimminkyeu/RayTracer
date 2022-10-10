/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 23:30:53 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/10 20:35:09 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_color.h"
#include "gl_draw.h"
#include "gl_vec4.h"
#include "gl_vec3.h"
#include "gl_vec2.h"
#include "libft.h"
#include "main.h"

// screen 좌표계를 world 좌표계로 변환.
t_vec3 transform_screen_to_world(t_image *img, t_vec2 pos_screen)
{
	const float x_scale = 2.0f / img->img_size.width;
	const float y_scale = 2.0f / img->img_size.height;
	const float aspect_ratio = (float)img->img_size.width / img->img_size.height;

	// 3차원 공간으로 확장.
	return (gl_vec3_3f((pos_screen.x * x_scale - 1.0f) * aspect_ratio, -pos_screen.y * y_scale + 1.0f, 0.0f));
}

t_vec3 trace_ray(t_device *device, t_ray *ray)
{
	// test code for ray_tracing
	if (device->objects.spheres->size == 0)
		gl_vec3_1f(0.0f);

	t_sphere *sphere = device->objects.spheres->data[0];
	t_hit hit = sphere_intersect_ray_collision(ray, sphere);

	if (hit.distance < 0.0f)
	{
		return (gl_vec3_1f(220.0f)); // return black
	}
	else
	{
		printf("hit: %f\n", hit.distance);
		return (gl_vec3_multiply_scalar(sphere->color, hit.distance));
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

			t_vec3 tmp = gl_vec3_clamp(trace_ray(device, &pixel_ray), gl_vec3_1f(0.0f), gl_vec3_1f(1.0f));
			int final_color = gl_get_color_from_vec4(gl_vec4_4f(tmp.b, tmp.g, tmp.r, 0.0f));
			// (void)tmp;
			// int final_color = WHITE;
			gl_draw_pixel(img, x, y, final_color);
			// printf("x:%f y:%f, color:%d\n", pixel_pos_world.x, pixel_pos_world.y, final_color);
			x++;
		}
		y++;
	}


	return (0);
}
