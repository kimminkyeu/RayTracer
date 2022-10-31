/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 22:57:12 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/31 22:57:24 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace_ray.h"
#include "gl_vec3.h"

/* ---------------------------------------
 * |  NOTE:  Main Ray-tracing Algorithm  |
 ----------------------------------------*/

/** trace each ray's hit-object, then calcuate color with Phong-model. */
t_vec3	trace_ray(t_device *device, const t_ray *ray, \
					const int reflection_recursive_level)
{
	t_hit	hit;

	if (reflection_recursive_level < 0)
		return (vec3_1f(0.0f));
	hit = find_closet_collision(device, ray);
	if (hit.distance >= 0.0f)
		return (calculate_pixel_color(device, ray, hit, \
						reflection_recursive_level));
	else
		return (device->renderer_settings.sky_color);
}

t_hit	find_closet_collision(t_device *device, const t_ray *ray)
{
	float	closest_distance;
	t_hit	closest_hit;
	t_hit	hit_result;
	size_t	i;

	closest_distance = FLT_MAX;
	closest_hit = create_hit(-1.0f, vec3_1f(0.0f), vec3_1f(0.0f));
	i = 0;
	while (i < device->objects->size)
	{
		hit_result = check_ray_collision(ray, device->objects->data[i]);
		if (hit_result.distance >= 0.0f \
				&& hit_result.distance < closest_distance)
		{
			closest_distance = hit_result.distance;
			closest_hit = hit_result;
			closest_hit.obj = device->objects->data[i];
		}
		i++;
	}
	return (closest_hit);
}

t_vec3	calculate_pixel_color(t_device *device, const t_ray *ray, \
				t_hit hit, const int reflection_recursive_level)
{
	t_vec3	phong_color;
	t_light	*light_each;
	size_t	i;

	if (hit.obj->normal_texture != NULL \
			&& device->is_high_resolution_render_mode == true)
		hit.normal = sample_normal_map(&hit);
	i = 0;
	phong_color = vec3_1f(0.0f);
	while (i < device->point_lights->size)
	{
		light_each = device->point_lights->data[i];
		phong_color = add3(phong_color, \
			calculate_phong(device, ray, hit, light_each));
		i++;
	}
	if (hit.obj->material.reflection)
		phong_color = add3(phong_color, calculate_reflection(\
			device, ray, hit, reflection_recursive_level));
	if (hit.obj->material.transparency)
		phong_color = add3(phong_color, calculate_refraction(\
			device, ray, hit, reflection_recursive_level));
	return (phong_color);
}
