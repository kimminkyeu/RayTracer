/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_shading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 22:37:25 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/31 23:01:04 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_vec3.h"
#include "trace_ray.h"

/** (1) Calcaultate Ambient texture
 		: used bilinear interpolation for texture sampling. */
t_vec3	calcuate_ambient(t_device *device, t_hit hit)
{
	t_vec3	ambient_color;
	t_vec3	sample_ambient;

	ambient_color = mult3_scalar(device->ambient_light->color, \
									device->ambient_light->brightness_ratio);
	if (hit.obj->diffuse_texture != NULL)
	{
		if (hit.obj->diffuse_texture->type == TEXTURE_CHECKER)
			sample_ambient = sample_point(hit.obj->diffuse_texture, \
											hit.uv, false);
		else
			sample_ambient = sample_linear(hit.obj->diffuse_texture, \
											hit.uv, false);
		ambient_color = mult3(ambient_color, sample_ambient);
	}
	else
	{
		ambient_color.r *= (hit.obj->material.diffuse.r / 255.0f);
		ambient_color.g *= (hit.obj->material.diffuse.g / 255.0f);
		ambient_color.b *= (hit.obj->material.diffuse.b / 255.0f);
	}
	return (mult3_scalar(ambient_color, \
		1.0f - hit.obj->material.reflection - hit.obj->material.transparency));
}

/** check if hit_point is inside the shadow area. */
bool	is_in_shadow(t_device *device, t_hit hit, t_light *light, \
						const t_vec3 hit_point_to_light)
{
	const t_ray		shadow_ray = create_ray(add3(hit.point, \
		mult3_scalar(hit_point_to_light, 0.001f)), hit_point_to_light);
	const t_hit		shadow_ray_hit = find_closet_collision(\
		device, &shadow_ray);

	if (shadow_ray_hit.distance < 0.0f \
			|| shadow_ray_hit.obj->material.transparency > 0.0f \
			|| shadow_ray_hit.distance > len3(sub3(light->pos, \
											hit.point)))
	{
		return (false);
	}
	else
		return (true);
}

/** Calculate Diffuse color */
t_vec3	calculate_diffuse(t_hit hit, t_light *light, t_vec3 hit_point_to_light)
{
	const float	_diff = max_float(dot3(hit.normal, hit_point_to_light), 0.0f) \
						* light->brightness_ratio;
	t_vec3		diffuse_final;
	t_vec3		sample_diffuse;
	t_vec3		diffuse;

	diffuse_final = mult3_scalar(light->color, _diff);
	if (hit.obj->diffuse_texture != NULL)
	{
		if (hit.obj->diffuse_texture->type == TEXTURE_CHECKER)
			sample_diffuse = sample_point(hit.obj->diffuse_texture, \
											hit.uv, false);
		else
			sample_diffuse = sample_linear(hit.obj->diffuse_texture, \
											hit.uv, false);
		return (mult3(diffuse_final, sample_diffuse));
	}
	diffuse = mult3_scalar(hit.obj->material.diffuse, _diff);
	diffuse_final.r *= diffuse.r / 255.0f;
	diffuse_final.g *= diffuse.g / 255.0f;
	diffuse_final.b *= diffuse.b / 255.0f;
	return (diffuse_final);
}

/** Calculate Specular [ 2 * (N . L)N - L ] */
t_vec3	calcalate_specular(const t_ray *ray, t_hit hit, \
							t_light *light, t_vec3 hit_point_to_light)
{
	const t_vec3	spec_reflection_dir = sub3(mult3_scalar(\
					mult3_scalar(hit.normal, dot3(hit_point_to_light, \
					hit.normal)), 2.0f), hit_point_to_light);
	const float		_spec = powf(max_float(dot3(\
					vec3_reverse(ray->direction), \
					spec_reflection_dir), 0.0f), \
					hit.obj->material.alpha * light->brightness_ratio);
	const t_vec3	specular_final = mult3_scalar(mult3_scalar(\
					light->color, _spec), hit.obj->material.ks);

	return (mult3_scalar(specular_final, light->brightness_ratio));
}

/** To avoid hit at ray's starting point,
 * move shadow_ray toward forward direction.
 *	(1) [soft-shadow]
 * https://blog.imaginationtech.com
 * /implementing-fast-ray-traced-soft-shadows-in-a-game-engine/
 * */
t_vec3	calculate_phong(t_device *device, const t_ray *ray, \
						t_hit hit, t_light *light)
{
	const t_vec3	hit_point_to_light = normal3(\
									sub3(light->pos, hit.point));
	t_vec3			diffuse_color;
	t_vec3			specular_color;
	t_vec3			phong_color;

	phong_color = calcuate_ambient(device, hit);
	if (!is_in_shadow(device, hit, light, hit_point_to_light))
	{
		diffuse_color = calculate_diffuse(hit, light, hit_point_to_light);
		phong_color = add3(diffuse_color, phong_color);
		specular_color = calcalate_specular(ray, hit, \
			light, hit_point_to_light);
		phong_color = mult3_scalar(phong_color, \
						1.0f - hit.obj->material.reflection \
						- hit.obj->material.transparency);
		phong_color = add3(phong_color, specular_color);
	}
	return (phong_color);
}
