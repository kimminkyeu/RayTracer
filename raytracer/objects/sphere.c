/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:08:17 by minkyeki          #+#    #+#             */
/*   Updated: 2022/11/01 02:40:19 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_vec3.h"
#include "objects.h"
#include "ray.h"
#include "helper.h"
#include "sphere.h"

/** ------------------------------ *
 *  |     Sphere hit detection     |
 *  ------------------------------ */

#define PI (3.141592)

static t_vec3	calculate_determinant_d1_d2(\
		const t_ray *ray, t_sphere *sphere)
{
	float			d[3];
	const t_vec3	omc = sub3(ray->origin, sphere->center);
	const float		b = 2.0f * dot3(ray->direction, omc);
	const float		c = dot3(omc, omc) - sphere->radius * sphere->radius;
	const float		determinant = b * b - 4.0f * c;

	d[0] = determinant;
	d[1] = (-b - sqrtf(determinant)) / 2.0f;
	d[2] = (-b + sqrtf(determinant)) / 2.0f;
	return (vec3_3f(d[0], d[1], d[2]));
}

/** [ Sphere Intersection ]
 * --------------------------------------------------------
 * http://raytracerchallenge.com/bonus/texture-mapping.html
 * --------------------------------------------------------
 */

t_hit	sphere_intersect_ray_collision(const t_ray *ray, t_sphere *sphere)
{
	t_hit	hit;
	t_vec3	cal_v;
	t_vec3	d;

	cal_v = calculate_determinant_d1_d2(ray, sphere);
	hit = create_hit(-1.0f, vec3_1f(0.0f), vec3_1f(0.0f));
	if (cal_v.v[0] >= 0.0f)
	{
		hit.distance = min_float(cal_v.v[1], cal_v.v[2]);
		if (hit.distance < 0.0f)
			hit.distance = max_float(cal_v.v[1], cal_v.v[2]);
		hit.point
			= add3(ray->origin, mult3_scalar(ray->direction, hit.distance));
		hit.normal = normal3(sub3(hit.point, sphere->center));
		d = vec3_reverse(hit.normal);
		hit.uv.x = atan2(d.x, -d.z) / (2 * PI) + 0.5f;
		hit.uv.y = asin(d.y) / (PI) + 0.5f;
		hit.tangent = cross3(ray->direction, hit.normal);
	}
	return (hit);
}
