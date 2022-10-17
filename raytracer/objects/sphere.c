/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:08:17 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/17 18:59:51 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "objects.h"
# include "ray.h"
# include "helper.h"

/** ------------------------------ *
 *  |     Sphere hit detection     |
 *  ------------------------------ */

#define PI (3.141592)

t_hit sphere_intersect_ray_collision(t_ray *ray, t_sphere *sphere)
{
	t_hit	hit = create_hit(-1.0f, gl_vec3_1f(0.0f), gl_vec3_1f(0.0f));

	// const float a = gl_vec3_dot(ray->direction, ray->direction);
	const t_vec3 omc = gl_vec3_subtract_vector(ray->origin, sphere->center);
	const float b = 2.0f * gl_vec3_dot(ray->direction, omc);
	const float c = gl_vec3_dot(omc, omc) - sphere->radius * sphere->radius;
	const float determinant = b * b - 4.0f * c;

	if (determinant >= 0.0f)
	{
		const float d1 = (-b - sqrtf(determinant)) / 2.0f;
		const float d2 = (-b + sqrtf(determinant)) / 2.0f;

		hit.distance = min_float(d1, d2);
		hit.point = gl_vec3_add_vector(ray->origin, gl_vec3_multiply_scalar(ray->direction, hit.distance));
		hit.normal = gl_vec3_normalize(gl_vec3_subtract_vector(hit.point, sphere->center));

		// NOTE:  텍스춰링(texturing)에서 사용 (for Sampling)
		// -----------------------------------------------------------
		// (1) https://www.mvps.org/directx/articles/spheremap.htm
		// (2) https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/geometry/spherical-coordinates-and-trigonometric-functions
		// (3) https://gamedev.stackexchange.com/questions/114412/how-to-get-uv-coordinates-for-sphere-cylindrical-projection
		// (4) https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection

		// hit.uv.x = asin(hit.normal.x) / (PI) + 0.5;
		// hit.uv.y = asin(hit.normal.y) / (PI) + 0.5;

		// hit.uv.x = atan2(hit.normal.z, hit.normal.x) / (2 * PI) - 0.5;
		// hit.uv.y = hit.normal.y * 0.5 + 0.5;

		// (5) https://en.wikipedia.org/wiki/UV_mapping
		const t_vec3 d = gl_vec3_reverse(hit.normal);
		hit.uv.x = atan2(d.x, d.z) / (PI) + 0.5f; // 원래 2PI 였는데, 텍스쳐가 가로로 2배 늘어나서 PI로 바꿨더니 잘되더라.
		hit.uv.y = asin(d.y) / (PI) + 0.5f;
	}
	return (hit);
}
