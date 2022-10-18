/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:21:00 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/19 02:53:01 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ray.h"
# include "helper.h"
# include "plane.h"

/** ------------------------------ *
 *  |     Plain hit detection      |
 *  ------------------------------ */
t_hit plane_intersect_ray_collision(const t_ray *ray, t_plane *plane)
{
	t_hit	hit = create_hit(-1.0f, gl_vec3_1f(0.0f), gl_vec3_1f(0.0f));

	// 삼각형 하듯이, 단, 내부 영역에 있는지 없는지 검사만 안하면 된다.
	// 뒷면을 그리고 싶지 않은 경우 (Backface bulling)
	if (gl_vec3_dot(gl_vec3_reverse(ray->direction), plane->normal) < 0.0f) return (hit);
	// 평면과 광선이 수평에 매우 가깝다면 충돌하지 못하는 것으로 판단
	if (abs_float(gl_vec3_dot(ray->direction, plane->normal)) < 1e-2f) return (hit); // t 계산시 0으로 나누기 방지
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
