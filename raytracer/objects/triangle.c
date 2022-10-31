/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:09:34 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/27 22:03:58 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include <stdio.h>
# include "gl_vec3.h"
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

	// WARN:  이때 cross_product의 결과 벡터 방향은 음수, 즉 나를 향해 튀어나오는 경우이다.
	const t_vec3 v1v0 = sub3(v1, v0);
	const t_vec3 v2v0 = sub3(v2, v0);

/*
	#*        v1             v2
	#*	       *-------------*
	#*	       |          .
	#*	       |       .
	#*	       |    .
	#*	       | .
	#*	       *
	#*	      v0

	#*        uv1             uv2
	#*	       *-------------*
	#*	       |          .
	#*	       |       .
	#*	       |    .
	#*	       | .
	#*	       *
	#*	      uv0

*/

	*face_normal = normal3(cross3(v2v0, v1v0));

	// printf("tr : v0(%f,%f,%f), v1(%f,%f,%f), v2(%f,%f,%f)\n", v0.x, v0.y, v0.z, v1.x, v1.y, v1.z, v2.x, v2.y, v2.z);
	// printf("v2v0 : x(%f) y(%f) z(%f)\n", v2v0.x, v2v0.y, v2v0.z);
	// printf("v1v0 : x(%f) y(%f) z(%f)\n", v1v0.x, v1v0.y, v1v0.z);
	// printf("face normal of triangle : x(%f) y(%f) z(%f)\n", face_normal->x, face_normal->y, face_normal->z);
	// printf("ray_direction           : x(%f) y(%f) z(%f)\n", ray_dir.x, ray_dir.y, ray_dir.z);
	//  WARN:  주의! 삼각형의 넓이가 0일 경우에는 계산할 수 없음 (normalize에서 0으로 나누는 에러 발생)

	// 삼각형 뒷면을 그리고 싶지 않은 경우 (Backface bulling)
	if (dot3(vec3_reverse(ray_dir), *face_normal) < 0.0f) return false;

	// 평면과 광선이 수평에 매우 가깝다면 충돌하지 못하는 것으로 판단
	if (abs_float(dot3(ray_dir, *face_normal)) < 1e-2f) return false; // t 계산시 0으로 나누기 방지

	/* 2. 광선과 (무한히 넓은) 평면의 충돌 위치 계산 */
	*t = (dot3(v0, *face_normal) - dot3(ray_origin, *face_normal)) /
		 dot3(ray_dir, *face_normal);

	// 광선의 시작점 이전에 충돌한다면 렌더링할 필요 없음
	if (*t < 0.0f) return false;

	// 충돌 지점 계산
	*point = add3(ray_origin, mult3_scalar(ray_dir, *t));

	/* 3. 그 충돌 위치가 삼각형 안에 들어 있는 지 확인 */
	/*
#*---------------------------------*
#*  NOTE:   Vertax Clockwise Order |
#*---------------------------------*
#*                                 |
#*        v1            v2         |
#*	       *------------*          |
#*	       |          . |          |
#*	       |   p   .    |          |
#*	       |    .       |          |
#*	       | .          |          |
#*	       *------------*          |
#*	      v0            v3         |
#*                                 |
#*---------------------------------*
	*/

	const t_vec3 cross0 = cross3(sub3(*point, v0),
								 sub3(v1, v0));
	const t_vec3 cross1 = cross3(sub3(*point, v1),
								 sub3(v2, v1));
	const t_vec3 cross2 = cross3(sub3(*point, v2),
								 sub3(v0, v2));

	// 방향만 확인하면 되기 때문에 normalize() 생략 가능
	// 아래에서 cross product의 절대값으로 작은 삼각형들의 넓이 계산
	if (dot3(cross0, *face_normal) < 0.0f) return false;
	if (dot3(cross1, *face_normal) < 0.0f) return false;
	if (dot3(cross2, *face_normal) < 0.0f) return false;

	const float area0 = len3(cross0) * 0.5f;
	const float area1 = len3(cross1) * 0.5f;
	const float area2 = len3(cross2) * 0.5f;

	const float area_sum = area0 + area1 + area2;
	*w0 = area0 / area_sum;
	*w1 = area1 / area_sum;

	return (true);
}

// NOTE:  텍스춰링(texturing)에서 사용 (for Sampling)
// (uv0 * w0 + uv1 * w1 + uv2 * (1.0f - w0 - w1))
t_hit triangle_intersect_ray_collision(const t_ray *ray, t_triangle *triangle)
{
	t_hit	hit = create_hit(-1.0f, vec3_1f(0.0f), vec3_1f(0.0f));

	t_vec3 point, face_normal;
	float t, w0, w1;

	if (intersect_ray_triangle(ray->origin, ray->direction,
								triangle->v0, triangle->v1, triangle->v2,
								&point, &face_normal, &t, &w0, &w1))
	{
		hit.distance = t;
		hit.point = point; // ray.start + ray.dir * t;
		hit.normal = face_normal;

		hit.uv = mult2_scalar(triangle->uv0, w0);
		hit.uv = add2(mult2_scalar(triangle->uv1, w1), hit.uv);
		hit.uv = add2(mult2_scalar(triangle->uv2, (1.0f - w0 - w1)),
					  hit.uv);

		// t1 과 t2의 tangent가 서로 반대방향인 문제가 발생함.
		// * .  FIX:    아래 부분 반드시 고치기!
		const t_vec3 t0 = sub3(triangle->v1, triangle->v0);
		hit.tangent = normal3(cross3(hit.normal, t0));
	}

	return (hit);
}
