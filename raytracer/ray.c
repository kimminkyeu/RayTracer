/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:12:52 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/11 14:43:01 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/** helper function. (min) */
float minf(float f1, float f2)
{
	if (f1 >= f2)
		return (f2);
	else
		return (f1);
}

float maxf(float f1, float f2)
{
	if (f1 >= f2)
		return (f1);
	else
		return (f2);
}

t_ray create_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray ray;
	ray.origin = origin;
	ray.direction = direction;

	return (ray);
}

t_hit sphere_intersect_ray_collision(t_ray *ray, t_sphere *sphere)
{
	t_hit	hit;

	hit.distance = -1.0f;
	hit.normal = gl_vec3_1f(0.0f);
	hit.point = gl_vec3_1f(0.0f);

	// const float a = gl_vec3_dot(ray->direction, ray->direction);
	const t_vec3 omc = gl_vec3_subtract_vector(ray->origin, sphere->center);
	const float b = 2.0f * gl_vec3_dot(ray->direction, omc);
	const float c = gl_vec3_dot(omc, omc) - sphere->radius * sphere->radius;
	const float determinant = b * b - 4.0f * c;

	if (determinant >= 0.0f)
	{
		const float d1 = (-b - sqrtf(determinant)) / 2.0f;
		const float d2 = (-b + sqrtf(determinant)) / 2.0f;

		hit.distance = minf(d1, d2);
		hit.point = gl_vec3_add_vector(ray->origin, gl_vec3_multiply_scalar(ray->direction, hit.distance));
		hit.normal = gl_vec3_normalize(gl_vec3_subtract_vector(hit.point, sphere->center));
	}
	return (hit);
}
