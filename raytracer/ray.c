/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:12:52 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/13 17:02:47 by minkyeki         ###   ########.fr       */
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

/** helper function. (abs) */
float absf(float f)
{
	if (f >= 0.0f)
		return (f);
	else
		return (-f);
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

t_triangle create_triangle(t_vec3 v0, t_vec3 v1, t_vec3 v2)
{
	t_triangle t;

	t.v0 = v0;
	t.v1 = v1;
	t.v2 = v2;
	return (t);
}

/** ------------------------------ *
 *  |    Triangle hit detection    |
 *  ------------------------------ */
// 수학 프로그래밍을 좋아하시는 분들은 직접 구현해보시면 좋고,
// 대부분은 개념만 이해해두시고 활용하는 방향으로 접근하셔도 충분합니다.
// 잘 이해가 가지 않는다면 여러 자료로 교차 검증하면서 공부하시는 방법도
// 좋습니다. 참고:
// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
bool intersect_ray_triangle(t_vec3 ray_origin, t_vec3 ray_dir,
							t_vec3 v0, t_vec3 v1, t_vec3 v2,
							t_vec3 *point, t_vec3 *face_normal,
							float *t, float *u, float *v)
{
	// (void)ray_origin; (void)ray_dir; (void)v1; (void)v0; (void)v2; (void)point; (void)face_normal;
	// (void)t;
	(void)u; (void)v;
	/*
	 * 기본 전략
	 * - 삼각형이 놓여있는 평면과 광선의 교점을 찾고,
	 * - 그 교점이 삼각형 안에 있는지 밖에 있는지를 판단한다.
	 */

	/* 1. 삼각형이 놓여 있는 평면의 수직 벡터 계산 (glm::cross) */
	const t_vec3 v1v0 = gl_vec3_subtract_vector(v1, v0);
	const t_vec3 v2v0 = gl_vec3_subtract_vector(v2, v0);

	*face_normal = gl_vec3_normalize(gl_vec3_cross(v1v0, v2v0));
	//  WARN:  주의! 삼각형의 넓이가 0일 경우에는 계산할 수 없음 (normalize에서 0으로 나누는 에러 발생)

	// 삼각형 뒷면을 그리고 싶지 않은 경우 (Backface bulling)
	if (gl_vec3_dot(gl_vec3_reverse(ray_dir), *face_normal) < 0.0f) return false;

	// 평면과 광선이 수평에 매우 가깝다면 충돌하지 못하는 것으로 판단
	if (absf(gl_vec3_dot(ray_dir, *face_normal)) < 1e-2f) return false; // t 계산시 0으로 나누기 방지

	/* 2. 광선과 (무한히 넓은) 평면의 충돌 위치 계산 */
	*t = (gl_vec3_dot(v0, *face_normal) - gl_vec3_dot(ray_origin, *face_normal)) / gl_vec3_dot(ray_dir, *face_normal);

	// 광선의 시작점 이전에 충돌한다면 렌더링할 필요 없음
	if (*t < 0.0f) return false;

	// 충돌 지점 계산
	*point = gl_vec3_add_vector(ray_origin, gl_vec3_multiply_scalar(ray_dir, *t));

	/* 3. 그 충돌 위치가 삼각형 안에 들어 있는 지 확인 */

	// 작은 삼각형들 3개의 normal 계산. 이때, ( WARN:  cross-product는 오른손 좌표계)
	// 이때, 방향만 알면 되기 때문에 normalize를 할 필요가 없음.
	// const t_vec3 normal0 = gl_vec3_normalize(gl_vec3_cross(gl_vec3_subtract_vector(*point, v2), gl_vec3_subtract_vector(v1, v2)));
	const t_vec3 normal0 = gl_vec3_cross(gl_vec3_subtract_vector(*point, v2), gl_vec3_subtract_vector(v1, v2));
	// const t_vec3 normal1 = gl_vec3_normalize(gl_vec3_cross(gl_vec3_subtract_vector(*point, v0), gl_vec3_subtract_vector(v2, v0)));
	const t_vec3 normal1 = gl_vec3_cross(gl_vec3_subtract_vector(*point, v0), gl_vec3_subtract_vector(v2, v0));
	// const t_vec3 normal2 = gl_vec3_normalize(gl_vec3_cross(gl_vec3_subtract_vector(v1, v0), gl_vec3_subtract_vector(*point, v0)));
	const t_vec3 normal2 = gl_vec3_cross(gl_vec3_subtract_vector(v1, v0), gl_vec3_subtract_vector(*point, v0));

	// 방향만 확인하면 되기 때문에 normalize() 생략 가능
	// 아래에서 cross product의 절대값으로 작은 삼각형들의 넓이 계산

	if (gl_vec3_dot(normal0, *face_normal) < 0.0f) return false;
	if (gl_vec3_dot(normal1, *face_normal) < 0.0f) return false;
	if (gl_vec3_dot(normal2, *face_normal) < 0.0f) return false;

	// Barycentric coordinates 계산
	// 텍스춰링(texturing)에서 사용
	// u = ...
	// v = ...

	return (true);
}

t_hit triangle_intersect_ray_collision(t_ray *ray, t_triangle *triangle)
{
	t_hit	hit = create_hit(-1.0f, gl_vec3_1f(0.0f), gl_vec3_1f(0.0f));

	t_vec3 point, face_normal;
	float t, u, v;

	// intersect ray_triangle 에서 point, face_normal, t, uv 값을 계산해서 대입해준다.
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


/** ------------------------------ *
 *  |     Square hit detection     | --> 무한 평면이 아닌 4개의 point를 입력하는 사각형.
 *  ------------------------------ */
t_hit square_intersect_ray_collision(t_ray *ray, t_square *square)
{
	// Create two triangle. check each.
	t_triangle t1 = create_triangle(square->v0, square->v1, square->v2);
	t_hit h1 = triangle_intersect_ray_collision(ray, &t1);

	t_triangle t2 = create_triangle(square->v0, square->v2, square->v3);
	t_hit h2 = triangle_intersect_ray_collision(ray, &t2);

	if (h1.distance >= 0.0f && h2.distance >= 0.0f)
	{
		if (h1.distance < h2.distance)
			return (h1);
		else
			return (h2);
	}
	else if (h1.distance >= 0.0f)
	{
		return (h1);
	}
	else
	{
		return (h2);
	}
}

/** ------------------------------ *
 *  |     Plain hit detection      |
 *  ------------------------------ */
t_hit plane_intersect_ray_collision(t_ray *ray, t_plane *plane)
{
	t_hit	hit = create_hit(-1.0f, gl_vec3_1f(0.0f), gl_vec3_1f(0.0f));

	// 삼각형 하듯이, 단, 내부 영역에 있는지 없는지 검사만 안하면 된다.
	// 뒷면을 그리고 싶지 않은 경우 (Backface bulling)
	if (gl_vec3_dot(gl_vec3_reverse(ray->direction), plane->normal) < 0.0f) return (hit);
	// 평면과 광선이 수평에 매우 가깝다면 충돌하지 못하는 것으로 판단
	if (absf(gl_vec3_dot(ray->direction, plane->normal)) < 1e-2f) return (hit); // t 계산시 0으로 나누기 방지
	/* 2. 광선과 (무한히 넓은) 평면의 충돌 위치 계산 */
	const float t = (gl_vec3_dot(plane->pos, plane->normal) - gl_vec3_dot(ray->origin, plane->normal)) / gl_vec3_dot(ray->direction, plane->normal);
	// 광선의 시작점 이전에 충돌한다면 렌더링할 필요 없음
	if (t < 0.0f) return (hit);
	// 충돌 지점 계산
	hit.point = gl_vec3_add_vector(ray->origin, gl_vec3_multiply_scalar(ray->direction, t));
	hit.distance = t;
	hit.normal = plane->normal;

	return (hit);
}

/** ------------------------------ *
 *  |     Sphere hit detection     |
 *  ------------------------------ */
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
