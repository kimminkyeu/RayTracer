/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:08:17 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/29 22:12:22 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "objects.h"
# include "ray.h"
# include "helper.h"

/** ------------------------------ *
 *  |     Sphere hit detection     |
 *  ------------------------------ */

#define PI (3.141592)

t_hit sphere_intersect_ray_collision(const t_ray *ray, t_sphere *sphere)
{
	t_hit	hit = create_hit(-1.0f, vec3_1f(0.0f), vec3_1f(0.0f));

	// const float a = dot3(ray->direction, ray->direction);
	const t_vec3 omc = sub3(ray->origin, sphere->center);
	const float b = 2.0f * dot3(ray->direction, omc);
	const float c = dot3(omc, omc) - sphere->radius * sphere->radius;
	const float determinant = b * b - 4.0f * c;

	if (determinant >= 0.0f)
	{
		const float d1 = (-b - sqrtf(determinant)) / 2.0f;
		const float d2 = (-b + sqrtf(determinant)) / 2.0f;

		hit.distance = min_float(d1, d2);

		// 투명 물체의 경우 물체 안에서 다시 밖으로 나가면서 충돌 가능.
		// 이 경우 더 큰 값을 hit_point로 사용.
		if (hit.distance < 0.0f)
		{
			hit.distance = max_float(d1, d2);
		}



		hit.point = add3(ray->origin,
						 mult3_scalar(ray->direction, hit.distance));
		hit.normal = normal3(sub3(hit.point, sphere->center));

		// *  NOTE:  텍스춰링(texturing)에서 사용 (for Sampling)
		// * -----------------------------------------------------------
		// * (1) https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/geometry/spherical-coordinates-and-trigonometric-functions
		// * (2) https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
		// * (3) https://en.wikipedia.org/wiki/UV_mapping

		const t_vec3 d = vec3_reverse(hit.normal);
		hit.uv.x = atan2(d.x, -d.z) / (2 * PI) + 0.5f;
		hit.uv.y = asin(d.y) / (PI) + 0.5f;
		// * -----------------------------------------------------------

		// *  NOTE:  Bump Map( = Normal Map) 에서 사용하기 위한 변수 계산.
		// * (1) http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/
		// * (2) https://mgun.tistory.com/m/1289
		// * (3) https://computergraphics.stackexchange.com/questions/1945/ray-tracing-tangent-space-for-a-point-on-a-sphere
		// ray_direction과 normal_vector를 cross하면 tangent를 구할 수 있다.
		// hit.tangent = normal3(cross3(ray->direction, hit.normal));
		hit.tangent = cross3(ray->direction, hit.normal);
	}
	return (hit);
}
