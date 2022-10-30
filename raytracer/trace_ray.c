/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 22:57:12 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/30 14:14:47 by kyeu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace_ray.h"
#include "gl_device.h"
#include "gl_vec3.h"
#include "hit.h"
#include "ray.h"

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

/** (1) Calcaultate Ambient texture 
 *		: used bilinear interpolation for texture sampling. */
t_vec3	calcuate_ambient(t_device *device, t_hit hit)
{
	t_vec3	ambient_color;
	t_vec3	sample_ambient;

	ambient_color = gl_vec3_multiply_scalar(device->ambient_light->color, device->ambient_light->brightness_ratio);
	if (hit.obj->diffuse_texture != NULL)
	{
		if (hit.obj->diffuse_texture->type == TEXTURE_CHECKER)
			sample_ambient = sample_point(hit.obj->diffuse_texture, hit.uv, false);
		else
			sample_ambient = sample_linear(hit.obj->diffuse_texture, hit.uv, false);
		ambient_color.r *= sample_ambient.b;
		ambient_color.g *= sample_ambient.g;
		ambient_color.b *= sample_ambient.r;
	}
	else
	{
		ambient_color.r *= (hit.obj->material.diffuse.r / 255.0f);
		ambient_color.g *= (hit.obj->material.diffuse.g / 255.0f);
		ambient_color.b *= (hit.obj->material.diffuse.b / 255.0f);
	}
	return (ambient_color);
}

/** check if hit_point is inside the shadow area. */
bool is_in_shadow(t_device *device, t_hit hit, t_light *light, const t_vec3 hit_point_to_light)
{
	const t_ray		shadow_ray = create_ray(gl_vec3_add_vector(hit.point, gl_vec3_multiply_scalar(hit_point_to_light, 1e-4f)), hit_point_to_light);
	const t_hit		shadow_ray_hit = find_closet_collision(device, &shadow_ray);

	if (shadow_ray_hit.distance < 0.0f \
			|| shadow_ray_hit.obj->material.transparency > 0.0f \
			|| shadow_ray_hit.distance > gl_vec3_get_magnitude(gl_vec3_subtract_vector(light->pos, hit.point)))
	{
		return (false);
	}
	else
		return (true);
}

/* Test code */
t_vec3	calculate_diffuse_2(t_hit hit, t_light *light, t_vec3 hit_point_to_light)
{
	const float	_diff = max_float(gl_vec3_dot(hit.normal, hit_point_to_light), 0.0f) * light->brightness_ratio;
	t_vec3		diffuse_final;
	t_vec3		sample_diffuse;

	diffuse_final = gl_vec3_multiply_scalar(light->color, _diff);
	if (hit.obj->diffuse_texture != NULL)
	{
		if (hit.obj->diffuse_texture->type == TEXTURE_CHECKER)
			sample_diffuse = sample_point(hit.obj->diffuse_texture, hit.uv, false);
		else
			sample_diffuse = sample_linear(hit.obj->diffuse_texture, hit.uv, false);
		diffuse_final.r *= sample_diffuse.r;
		diffuse_final.g *= sample_diffuse.g;
		diffuse_final.b *= sample_diffuse.b;
	}
	else
	{
		const t_vec3 diffuse = gl_vec3_multiply_scalar(hit.obj->material.diffuse, _diff);
		diffuse_final.r *= diffuse.r / 255.0f;
		diffuse_final.g *= diffuse.g / 255.0f;
		diffuse_final.b *= diffuse.b / 255.0f;

	}
	return (diffuse_final);
}

/** Calculate Diffuse color */
t_vec3	calculate_diffuse(t_hit hit, t_light *light, t_vec3 hit_point_to_light)
{
	const float	_diff = max_float(gl_vec3_dot(hit.normal, hit_point_to_light), 0.0f) * light->brightness_ratio;
	t_vec3		diffuse_final;
	t_vec3		sample_diffuse;

	diffuse_final = gl_vec3_1f(0.0f);
	if (hit.obj->diffuse_texture != NULL)
	{
		if (hit.obj->diffuse_texture->type == TEXTURE_CHECKER)
			sample_diffuse = sample_point(hit.obj->diffuse_texture, hit.uv, true);
		else
			sample_diffuse = sample_linear(hit.obj->diffuse_texture, hit.uv, true);
		diffuse_final.r = _diff * sample_diffuse.b;
		diffuse_final.g = _diff * sample_diffuse.g;
		diffuse_final.b = _diff * sample_diffuse.r;
	}
	else
	{
		diffuse_final = gl_vec3_multiply_scalar(hit.obj->material.diffuse, _diff);
		diffuse_final = gl_vec3_add_vector(diffuse_final, gl_vec3_multiply_scalar(light->color, _diff));
	}
	return (diffuse_final);
}

/** (4-1) Calculate Specular [ 2 * (N . L)N - L ] */
t_vec3	calcalate_specular(const t_ray *ray, t_hit hit, t_light *light, t_vec3 hit_point_to_light)
{
	const t_vec3	spec_reflection_dir = gl_vec3_subtract_vector(gl_vec3_multiply_scalar(gl_vec3_multiply_scalar(hit.normal, gl_vec3_dot(hit_point_to_light, hit.normal)), 2.0f), hit_point_to_light);
	const float		_spec = powf(max_float(gl_vec3_dot(gl_vec3_reverse(ray->direction), spec_reflection_dir), 0.0f), hit.obj->material.alpha * light->brightness_ratio);
	const t_vec3	specular_final = gl_vec3_multiply_scalar(gl_vec3_multiply_scalar(hit.obj->material.specular, _spec), hit.obj->material.ks);

	return (gl_vec3_multiply_scalar(specular_final, light->brightness_ratio));
}

/** To avoid hit at ray's starting point, move shadow_ray toward forward direction.
 * ----------------------------------------------------------------------------------
 *	(1) [soft-shadow] https://blog.imaginationtech.com/implementing-fast-ray-traced-soft-shadows-in-a-game-engine/
 * */
t_vec3 calculate_phong(t_device *device, const t_ray *ray, t_hit hit, t_light *light)
{
	const t_vec3	hit_point_to_light = gl_vec3_normalize(gl_vec3_subtract_vector(light->pos, hit.point));
	const t_vec3		ambient_color = calcuate_ambient(device, hit);
	t_vec3		diffuse_color;
	t_vec3			specular_color;
	t_vec3			phong_color;

	phong_color = gl_vec3_1f(0.0f);
	if (!is_in_shadow(device, hit, light, hit_point_to_light))
	{	
		/** diffuse_color = calculate_diffuse(hit, light, hit_point_to_light); */

		diffuse_color = calculate_diffuse_2(hit, light, hit_point_to_light);


		specular_color = calcalate_specular(ray, hit, light, hit_point_to_light);
		phong_color = gl_vec3_add_vector(diffuse_color, ambient_color);
		phong_color = gl_vec3_multiply_scalar(phong_color, 1.0f - hit.obj->material.reflection - hit.obj->material.transparency);
		phong_color = gl_vec3_add_vector(phong_color, specular_color);
	}
	return (phong_color);
}

// d - 2( n . d )n
// move ray slightly to it's direction to avoid early hit.
t_vec3 calculate_reflection(t_device *device, const t_ray *ray, t_hit hit, const int reflection_recursive_level)
{
	const t_vec3	reflected_ray_dir = gl_vec3_subtract_vector(ray->direction, (gl_vec3_multiply_scalar(gl_vec3_multiply_scalar(hit.normal, gl_vec3_dot(ray->direction, hit.normal)), 2.0f)));
	const t_vec3	hit_point_offset = gl_vec3_add_vector(hit.point, gl_vec3_multiply_scalar(reflected_ray_dir, 1e-4f));
	const t_ray		reflected_ray = create_ray(hit_point_offset, reflected_ray_dir);
	const t_vec3	reflected_color = trace_ray(device, &reflected_ray, reflection_recursive_level - 1);
	return (gl_vec3_multiply_scalar(reflected_color, hit.obj->material.reflection));
}

/** [ How to Calcaute Refraction ]
 * ------------------------------------------------------------------------
 * (1) https://samdriver.xyz/article/refraction-sphere
 * (2) https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
 * (3) https://web.cse.ohio-state.edu/~shen.94/681/Site/Slides_files/reflection_refraction.pdf
 * (4) https://lifeisforu.tistory.com/384 
 * -------------------------------------------------------------------------
 *  use [ cos^2 + sin^2 = 1 ] to calculate refracted direction.
 *
 *  IOR : Index of Refraction (Glass 1.5 | Water 1.3).
 *  eta : sinThera1 / sinTheta2
 *
 *  if ray is going inside the object, then (eta = IOR)
 *  if ray is going outside of the object, then (eta = 1.0f / IOR)
 *  
 */
t_vec3 calculate_refraction(t_device *device, const t_ray *ray, t_hit hit, const int reflection_recursive_level)
{
		const float	ior = 1.5f;
		float		eta;
		t_vec3		normal;

		if (gl_vec3_dot(ray->direction, hit.normal) < 0.0f)
		{
			eta = ior;
			normal = hit.normal;
		}
		else
		{
			eta = 1.0f / ior;
			normal = gl_vec3_reverse(hit.normal);
		}

		const float cosTheta1 = gl_vec3_dot(gl_vec3_reverse(ray->direction), normal);
		const float sinTheta1 = sqrtf(1.0f - cosTheta1 * cosTheta1) ; // cos^2 + sin^2 = 1
		const float sinTheta2 = sinTheta1 / eta ;
		const float cosTheta2 = sqrtf(1.0f - sinTheta2 * sinTheta2);

		const float m_0 = gl_vec3_dot(normal, gl_vec3_reverse(ray->direction));
		const t_vec3 m_1 = gl_vec3_add_vector(gl_vec3_multiply_scalar(normal, m_0), ray->direction);
		const t_vec3 m = gl_vec3_normalize(m_1);

		const t_vec3 A = gl_vec3_multiply_scalar(m, sinTheta2);
		const t_vec3 B = gl_vec3_multiply_scalar(gl_vec3_reverse(normal), cosTheta2);
		const t_vec3 refracted_direction = gl_vec3_normalize(gl_vec3_add_vector(A, B)); // Transmission

		t_vec3 offset = gl_vec3_multiply_scalar(refracted_direction, 0.0001f);
		t_ray refraction_ray = create_ray(gl_vec3_add_vector(hit.point, offset), refracted_direction);
		const t_vec3 refracted_color = trace_ray(device, &refraction_ray, reflection_recursive_level - 1);
		return (gl_vec3_multiply_scalar(refracted_color, hit.obj->material.transparency));
}

t_vec3 calculate_pixel_color(t_device *device, const t_ray *ray, t_hit hit, const int reflection_recursive_level)
{
	t_vec3	phong_color;
	t_light	*light_each;
	size_t	i;

	if (hit.obj->normal_texture != NULL && device->is_high_resolution_render_mode == true)
		hit.normal = sample_normal_map(&hit);
	i = 0;
	phong_color = gl_vec3_1f(0.0f);
	while (i < device->point_lights->size)
	{
		light_each = device->point_lights->data[i];
		phong_color = gl_vec3_add_vector(phong_color, calculate_phong(device, ray, hit, light_each));
		i++;
	}
	if (hit.obj->material.reflection)
		phong_color = gl_vec3_add_vector(phong_color, calculate_reflection(device, ray, hit, reflection_recursive_level));
	if (hit.obj->material.transparency)
		phong_color = gl_vec3_add_vector(phong_color, calculate_refraction(device, ray, hit, reflection_recursive_level));
	return (phong_color);
}

/* ---------------------------------------
 * |  NOTE:  Main Ray-tracing Algorithm  |
 ----------------------------------------*/

/** trace each ray's hit-object, then calcuate color with Phong-model. */
t_vec3 trace_ray(t_device *device, const t_ray *ray, const int reflection_recursive_level)
{
	t_hit	hit;

	if (reflection_recursive_level < 0)
		return (gl_vec3_1f(0.0f));
	hit = find_closet_collision(device, ray);
	if (hit.distance >= 0.0f)
	{
		return (calculate_pixel_color(device, ray, hit, reflection_recursive_level));
	}
	else
		return (gl_vec3_1f(0.0f));
}

t_hit find_closet_collision(t_device *device, const t_ray *ray)
{
	float	closest_distance;
	t_hit	closest_hit;
	t_hit	hit_result;
	size_t	i;

	closest_distance = FLT_MAX;
	closest_hit = create_hit(-1.0f, gl_vec3_1f(0.0f), gl_vec3_1f(0.0f));
	i = 0;
	while (i < device->objects->size)
	{
		hit_result = check_ray_collision(ray, device->objects->data[i]);
		if (hit_result.distance >= 0.0f && hit_result.distance < closest_distance)
		{
			closest_distance = hit_result.distance;
			closest_hit = hit_result;
			closest_hit.obj = device->objects->data[i];
		}
		i++;
	}
	return (closest_hit);
 }
