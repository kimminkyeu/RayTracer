/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 21:10:04 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/22 22:51:00 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disk.h"
#include "gl_vec3.h"
#include "helper.h"
#include "hit.h"

t_hit disk_intersect_ray_collision(const t_ray *ray, t_disk *disk)
{
	t_hit	hit = create_hit(-1.0f, gl_vec3_1f(0.0f), gl_vec3_1f(0.0f));

	// 뒷면을 그리고 싶지 않은 경우 (Backface bulling)
	// if (gl_vec3_dot(gl_vec3_reverse(ray->direction), disk->orientation) < 0.0f) return (hit);

	// 평면과 광선이 수평에 매우 가깝다면 충돌하지 못하는 것으로 판단
	if (abs_float(gl_vec3_dot(ray->direction, disk->orientation)) < 1e-2f) return (hit); // t 계산시 0으로 나누기 방지

	/* 2. 광선과 (무한히 넓은) 평면의 충돌 위치 계산 */
	const float t = (gl_vec3_dot(disk->center, disk->orientation) - gl_vec3_dot(ray->origin, disk->orientation)) / gl_vec3_dot(ray->direction, disk->orientation);

	// 광선의 시작점 이전에 충돌한다면 렌더링할 필요 없음
	if (t < 0.0f) return (hit);

	// 충돌 지점 계산
	hit.point = gl_vec3_add_vector(ray->origin, gl_vec3_multiply_scalar(ray->direction, t));
	hit.distance = t;
	hit.normal = disk->orientation;

	// 충돌 지점이 원 반지름 기준으로 안에 있는지 체크.
	const float hit_to_center = gl_vec3_get_magnitude(gl_vec3_subtract_vector(hit.point, disk->center));
	if (hit_to_center < disk->radius)
	{
		return (hit);
	}
	else
		return (create_hit(-1.0f, gl_vec3_1f(0.0f), gl_vec3_1f(0.0f)));
}
