/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 22:35:45 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/31 16:44:30 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace_ray.h"

/** [ How to Calcaute Refraction ]
 * 	Check photo of real transparent object later!
 *
 * (1) https://samdriver.xyz/article/refraction-sphere
 * (2) https://www.scratchapixel.com/lessons/3d-basic-rendering/
 * 			introduction-to-shading/reflection-refraction-fresnel
 * (3) https://web.cse.ohio-state.edu/~shen.94/681/Site/Slides_files/
 * 			reflection_refraction.pdf
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
t_vec3	get_refracted_direction(const t_ray *ray, float eta, t_vec3 normal)
{
	const float		cos_theta1 = dot3(vec3_reverse(ray->direction), normal);
	const float		sin_theta2 = sqrtf(1.0f - cos_theta1 * cos_theta1) / eta ;
	const float		cos_theta2 = sqrtf(1.0f - sin_theta2 * sin_theta2);
	const t_vec3	a = mult3_scalar(normal3(\
		add3(mult3_scalar(normal, dot3(normal, \
		vec3_reverse(ray->direction))), ray->direction)), sin_theta2);
	const t_vec3	b = mult3_scalar(vec3_reverse(normal), cos_theta2);

	return (normal3(add3(a, b)));
}

t_vec3	calculate_refraction(t_device *device, const t_ray *ray, \
							t_hit hit, const int reflection_recursive_level)
{
	float	eta;
	t_vec3	normal;
	t_vec3	refracted_direction;
	t_ray	refracted_ray;
	t_vec3	refracted_color;

	if (dot3(ray->direction, hit.normal) < 0.0f)
	{
		eta = hit.obj->material.ior;
		normal = hit.normal;
	}
	else
	{
		eta = 1.0f / hit.obj->material.ior;
		normal = vec3_reverse(hit.normal);
	}
	refracted_direction = get_refracted_direction(ray, eta, normal);
	refracted_ray = create_ray(add3(hit.point, mult3_scalar(\
					refracted_direction, 0.0001f)), refracted_direction);
	refracted_color = trace_ray(device, &refracted_ray, \
						reflection_recursive_level - 1);
	return (mult3_scalar(refracted_color, hit.obj->material.transparency));
}
