/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:08:17 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/31 17:44:12 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "ray.h"
#include "helper.h"

/** ------------------------------ *
 *  |     Sphere hit detection     |
 *  ------------------------------ */

#define PI (3.141592)

t_hit	sphere_intersect_ray_collision(const t_ray *ray, t_sphere *sphere)
{
	const t_vec3	omc = sub3(ray->origin, sphere->center);
	const float		b = 2.0f * dot3(ray->direction, omc);
	const float		c = dot3(omc, omc) - sphere->radius * sphere->radius;
	const float		determinant = b * b - 4.0f * c;
	t_hit			hit;

	hit = create_hit(-1.0f, vec3_1f(0.0f), vec3_1f(0.0f));
	if (determinant >= 0.0f)
	{
		const float d1 = (-b - sqrtf(determinant)) / 2.0f;
		const float d2 = (-b + sqrtf(determinant)) / 2.0f;
		hit.distance = min_float(d1, d2);
		if (hit.distance < 0.0f)
			hit.distance = max_float(d1, d2);
		hit.point
			= add3(ray->origin, mult3_scalar(ray->direction, hit.distance));
		hit.normal = normal3(sub3(hit.point, sphere->center));
		const t_vec3 d = vec3_reverse(hit.normal);
		hit.uv.x = atan2(d.x, -d.z) / (2 * PI) + 0.5f;
		hit.uv.y = asin(d.y) / (PI) + 0.5f;
		hit.tangent = cross3(ray->direction, hit.normal);
	}
	return (hit);
}
