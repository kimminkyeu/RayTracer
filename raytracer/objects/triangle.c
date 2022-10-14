/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:09:34 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/14 15:19:53 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "helper.h"
# include "objects.h"
# include "ray.h"

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
							float *t, float *w0, float *w1)
{
	// (void)ray_origin; (void)ray_dir; (void)v1; (void)v0; (void)v2; (void)point; (void)face_normal;
	// (void)t;
	(void)w0; (void)w1;
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
	if (abs_float(gl_vec3_dot(ray_dir, *face_normal)) < 1e-2f) return false; // t 계산시 0으로 나누기 방지

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
	float t, w0, w1;

	// intersect ray_triangle 에서 point, face_normal, t, uv 값을 계산해서 대입해준다.
	if (intersect_ray_triangle(ray->origin, ray->direction,
								triangle->v0, triangle->v1, triangle->v2,
								&point, &face_normal, &t, &w0, &w1))
	{
		hit.distance = t;
		hit.point = point; // ray.start + ray.dir * t;
		hit.normal = face_normal;

		// NOTE:  텍스춰링(texturing)에서 사용 (for Sampling)
		// (uv0 * w0 + uv1 * w1 + uv2 * (1.0f - w0 - w1))
		hit.uv = gl_vec2_multiply_scalar(triangle->uv0, w0);
		hit.uv = gl_vec2_add_vector(gl_vec2_multiply_scalar(triangle->uv1, w1), hit.uv);
		hit.uv = gl_vec2_add_vector(gl_vec2_multiply_scalar(triangle->uv2, (1.0f - w0 - w1)), hit.uv);
	}

	return (hit);
}
