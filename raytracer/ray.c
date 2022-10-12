/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:12:52 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/12 14:17:00 by minkyeki         ###   ########.fr       */
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

/** helper function. (max) */
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

t_hit create_hit(float distance, t_vec3 normal, t_vec3 point)
{
	t_hit	hit;

	hit.distance = distance;
	hit.normal = normal;
	hit.point = point;
	return (hit);
}

// 수학 프로그래밍을 좋아하시는 분들은 직접 구현해보시면 좋고,
// 대부분은 개념만 이해해두시고 활용하는 방향으로 접근하셔도 충분합니다.
// 잘 이해가 가지 않는다면 여러 자료로 교차 검증하면서 공부하시는 방법도
// 좋습니다. 참고:
// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
bool intersect_ray_triangle(t_vec3 orig, t_vec3 dir,
							t_vec3 v0, t_vec3 v1, t_vec3 v2,
							t_vec3 *point, t_vec3 *face_normal,
							float *t, float *u, float *v)
{
	(void)orig; (void)dir; (void)v1; (void)v0; (void)v2; (void)point; (void)face_normal;
	(void)t; (void)u; (void)v;
	/*
	 * 기본 전략
	 * - 삼각형이 놓여있는 평면과 광선의 교점을 찾고,
	 * - 그 교점이 삼각형 안에 있는지 밖에 있는지를 판단한다.
	 */

	/* 1. 삼각형이 놓여 있는 평면의 수직 벡터 계산 */
	// faceNormal = ...;
	//주의: 삼각형의 넓이가 0일 경우에는 계산할 수 없음

	// 삼각형 뒷면을 그리고 싶지 않은 경우 (Backface culling)
	// if (... < 0.0f) return false;

	// 평면과 광선이 수평에 매우 가깝다면 충돌하지 못하는 것으로 판단
	// if (... < 1e-2f) return false; // t 계산시 0으로 나누기 방지

	/* 2. 광선과 평면의 충돌 위치 계산 */
	// t = ...

	// 광선의 시작점 이전에 충돌한다면 렌더링할 필요 없음
	// if (...) return false;

	// point = orig + t * dir; // 충돌점

	/* 3. 그 충돌 위치가 삼각형 안에 들어 있는 지 확인 */

	// 작은 삼각형들 3개의 normal 계산
	// const vec3 normal0 = ...
	// const vec3 normal1 = ...
	// const vec3 normal2 = ...
	// 방향만 확인하면 되기 때문에 normalize() 생략 가능
	// 아래에서 cross product의 절대값으로 작은 삼각형들의 넓이 계산

	// if (dot(normal0, faceNormal) < 0.0f) return false;
	// if (dot(normal1, faceNormal) < 0.0f) return false;
	// if (dot(normal2, faceNormal) < 0.0f) return false;

	// Barycentric coordinates 계산
	// 텍스춰링(texturing)에서 사용
	// u = ...
	// v = ...

	return (false);
}

t_hit triangle_intersect_ray_collision(t_ray *ray, t_triangle *triangle)
{
	t_hit	hit = create_hit(-1.0f, gl_vec3_1f(0.0f), gl_vec3_1f(0.0f));

	t_vec3 point, face_normal;
	float t, u, v;

	if (intersect_ray_triangle(ray->origin, ray->direction,
								triangle->v0, triangle->v1, triangle->v2,
								&point, &face_normal, &t, &u, &v))
	{
		hit.distance = t;
		hit.point = point; // ray.start + ray.dir * t;
		hit.normal = face_normal;

		// 텍스춰링(texturing)에서 사용
		// hit.uv = uv0 * u + uv1 * v + uv2 * (1.0f - u - v);
	}

	return (hit);
}

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

		hit.distance = minf(d1, d2);
		hit.point = gl_vec3_add_vector(ray->origin, gl_vec3_multiply_scalar(ray->direction, hit.distance));
		hit.normal = gl_vec3_normalize(gl_vec3_subtract_vector(hit.point, sphere->center));
	}
	return (hit);
}
