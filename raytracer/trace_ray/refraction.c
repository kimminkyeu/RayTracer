/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 22:35:45 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/31 01:48:22 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace_ray.h"

t_vec3 get_refracted_direction(const t_ray *ray, float eta, t_vec3 normal)
{
	const float cosTheta1 = gl_vec3_dot(\
		gl_vec3_reverse(ray->direction), normal);
	const float sinTheta2 = sqrtf(1.0f - cosTheta1 * cosTheta1) / eta ;
	const float cosTheta2 = sqrtf(1.0f - sinTheta2 * sinTheta2);
	const t_vec3 A = gl_vec3_multiply_scalar(\
		gl_vec3_normalize(gl_vec3_add_vector(gl_vec3_multiply_scalar(\
			normal, gl_vec3_dot(normal, gl_vec3_reverse(\
				ray->direction))), ray->direction)), sinTheta2);
	const t_vec3 B = gl_vec3_multiply_scalar(\
		gl_vec3_reverse(normal), cosTheta2);

	return (gl_vec3_normalize(gl_vec3_add_vector(A, B)));
}


/** TODO:  Understand Math here! */
/*
t_vec3 get_refracted_direction(const t_ray *ray, float eta, t_vec3 normal)
{
	const float cosTheta1 = gl_vec3_dot(gl_vec3_reverse(ray->direction), normal);
	const float sinTheta1 = sqrtf(1.0f - cosTheta1 * cosTheta1);
	const float sinTheta2 = sinTheta1 / eta ;
	const float cosTheta2 = sqrtf(1.0f - sinTheta2 * sinTheta2);

	const float m_0 = gl_vec3_dot(normal, gl_vec3_reverse(ray->direction));
	const t_vec3 m_1 = gl_vec3_add_vector(gl_vec3_multiply_scalar(normal, m_0), ray->direction);
	const t_vec3 m = gl_vec3_normalize(m_1);

	const t_vec3 A = gl_vec3_multiply_scalar(m, sinTheta2);
	const t_vec3 B = gl_vec3_multiply_scalar(gl_vec3_reverse(normal), cosTheta2);
	return (gl_vec3_normalize(gl_vec3_add_vector(A, B)));
}
*/

/** [ How to Calcaute Refraction ]
 * 	Check photo of real transparent object later!
 *
 * (1) https://samdriver.xyz/article/refraction-sphere
 * (2) https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
 * (3) https://web.cse.ohio-state.edu/~shen.94/681/Site/Slides_files/reflection_refraction.pdf
 * (4) https://lifeisforu.tistory.com/384
 * -------------------------------------------------------------------------
 *
 *  IOR : Index of Refraction (Glass 1.5 | Water 1.3).
 *  eta : sinThera1 / sinTheta2
 *
 *  Use [ cos^2 + sin^2 = 1 ] to calculate refracted direction.
 *  if ray is going inside the object, then (eta = IOR)
 *  if ray is going outside of the object, then (eta = 1.0f / IOR)
 *
 *  TODO:  Fresenel + Caustics
 */
t_vec3 calculate_refraction(t_device *device, const t_ray *ray, \
							t_hit hit, const int reflection_recursive_level)
{
		float		eta;
		t_vec3		normal;
		t_vec3		refracted_direction;
		t_ray		refracted_ray;
		t_vec3		refracted_color;

		if (gl_vec3_dot(ray->direction, hit.normal) < 0.0f)
		{
			eta = hit.obj->material.ior;
			normal = hit.normal;
		}
		else
		{
			eta = 1.0f / hit.obj->material.ior;
			normal = gl_vec3_reverse(hit.normal);
		}
		refracted_direction = get_refracted_direction(ray, eta, normal);
		refracted_ray = create_ray(gl_vec3_add_vector(hit.point, gl_vec3_multiply_scalar(refracted_direction, 0.0001f)), refracted_direction);
		refracted_color = trace_ray(device, &refracted_ray, reflection_recursive_level - 1);
		return (gl_vec3_multiply_scalar(refracted_color, hit.obj->material.transparency));
}
