/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 22:41:35 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/30 22:43:48 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace_ray.h"

/**
 * dx : for super sampling. (Length of a single pixel)
 */
int do_ray_tracing_and_return_color(t_device *device, t_image *img, int x, int y)
{
	(void)device;
	const t_vec3	pixel_pos_world = transform_screen_to_camera_world(\
							device->camera, img, gl_vec2_2f(x, y));
	const float		dx = 2.0f / img->img_size.height;
	t_vec3			trace_result;
	int				final_color;

	trace_result = super_sampling_anti_aliasing(img, pixel_pos_world, dx, \
					device->renderer_settings.antialiasing_level);
	trace_result = gl_vec3_clamp(trace_result, \
								gl_vec3_1f(0.0f), gl_vec3_1f(255.0f));
	final_color = gl_get_color_from_vec4(\
		gl_vec4_4f(trace_result.b, trace_result.g, trace_result.r, 0.0f));
	return (final_color);
}


t_vec3 super_sampling_anti_aliasing(t_image *img, t_vec3 pixel_pos_world, const float dx, const int super_sampling_recursive_level)
{
	const float	sub_dx = 0.5f * dx;
	t_vec3		sample_colors[4];
	t_vec3		ray_dir;
	t_ray		pixel_ray;

	if (img->device_ptr->is_high_resolution_render_mode == false || super_sampling_recursive_level == 0)
	{
		ray_dir = gl_vec3_normalize(gl_vec3_subtract_vector(pixel_pos_world, img->device_ptr->camera->pos));
		pixel_ray = create_ray(pixel_pos_world, ray_dir);
		return (trace_ray(img->device_ptr, &pixel_ray, img->device_ptr->renderer_settings.reflection_level));
	}
	pixel_pos_world.x = pixel_pos_world.x - sub_dx * 0.5f;
	pixel_pos_world.y = pixel_pos_world.y - sub_dx * 0.5f;
	if (is_4_sub_pixels_are_same(img, pixel_pos_world, dx, sample_colors))
		return (sample_colors[0]);
	else
		return (do_recur_super_sampling(img, pixel_pos_world, sub_dx, super_sampling_recursive_level));
}

/**
 * NOTE:  Super Sampling (4 Pixels Each)
 * --------------------
 * | 1(0.25)*  2(0.75)|
 * |        *         |
 * |------- * ---------
 * | 3(0.25)* 4(0.75) |
 * |        *         |
 * --------------------*/
t_vec3	do_recur_super_sampling(t_image *img, t_vec3 pixel_pos_world, const float sub_dx, const int super_sampling_recursive_level)
{
	t_vec3	pixel_color;
	int 	i;
	int 	j;

	pixel_color = gl_vec3_1f(0.0f);
	j = 0;
	while (j < 2)
	{
		i = 0;
		while (i < 2)
		{
			t_vec3 sub_pos = gl_vec3_3f(pixel_pos_world.x + ((float)i * sub_dx),\
										pixel_pos_world.y + ((float)j * sub_dx),\
										pixel_pos_world.z);
			pixel_color = gl_vec3_add_vector(pixel_color, super_sampling_anti_aliasing(img, sub_pos, sub_dx, super_sampling_recursive_level - 1));
			i++;
		}
		j++;
	}
	return (gl_vec3_multiply_scalar(pixel_color, 0.25f));
}

/** Save 4 subpixel's data to t_vec3 *sample_color. */
void	update_4_sub_pixels(t_image *img, t_vec3 pixel_pos_world, const float dx, t_vec3 *sample_color)
{
	const float	sub_dx = 0.5f * dx;
	int i;
	int j;

	j = 0;
	while (j < 2)
	{
		i = 0;
		while (i < 2)
		{
			t_vec3 sub_pos = gl_vec3_3f(pixel_pos_world.x + ((float)i * sub_dx),\
										pixel_pos_world.y + ((float)j * sub_dx),\
										pixel_pos_world.z);
			t_vec3 ray_dir = gl_vec3_normalize(gl_vec3_subtract_vector(sub_pos, img->device_ptr->camera->pos));
			t_ray pixel_ray = create_ray(sub_pos, ray_dir);
			sample_color[j * 2 + i] = trace_ray(img->device_ptr, &pixel_ray, 1);
			i++;
		}
		j++;
	}

}

/** check if 4 colors are same */
bool	is_4_sub_pixels_are_same(t_image *img, t_vec3 pixel_pos_world, const float dx, t_vec3 *colors)
{
	int	i;

	i = 0;
	update_4_sub_pixels(img, pixel_pos_world, dx, colors);
	while (i < 3)
	{
		if (!(colors[i].r == colors[i+1].r \
			&& colors[i].g == colors[i+1].g \
			&& colors[i].b == colors[i+1].b))
			return (false);
		i++;
	}
	return (true);
}
