/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:08:17 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/18 21:56:38 by minkyeki         ###   ########.fr       */
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

		// *  NOTE:  텍스춰링(texturing)에서 사용 (for Sampling)
		// * -----------------------------------------------------------
		// * (1) https://www.mvps.org/directx/articles/spheremap.htm
		// * (2) https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/geometry/spherical-coordinates-and-trigonometric-functions
		// * (3) https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
		// * (4) https://en.wikipedia.org/wiki/UV_mapping
		const t_vec3 d = gl_vec3_reverse(hit.normal);
		hit.uv.x = atan2(d.x, d.z) / (PI) + 0.5f; // 원래 2PI 였는데, 텍스쳐가 가로로 2배 늘어나서 PI로 바꿨더니 잘되더라.
		hit.uv.y = asin(d.y) / (PI) + 0.5f;
		// * -----------------------------------------------------------


		// *  NOTE:  Bump Map( = Normal Map) 에서 사용하기 위한 변수 계산.
		// * (1) http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/
		// * (2) https://mgun.tistory.com/m/1289
		// * (3) https://computergraphics.stackexchange.com/questions/1945/ray-tracing-tangent-space-for-a-point-on-a-sphere
		// ray_direction과 normal_vector를 cross하면 tangent를 구할 수 있다.
		// hit.tangent = gl_vec3_normalize(gl_vec3_cross(ray->direction, hit.normal));
		hit.tangent = gl_vec3_cross(ray->direction, hit.normal);
	}
	return (hit);
}
