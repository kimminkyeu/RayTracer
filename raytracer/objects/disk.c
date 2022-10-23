#include "disk.h"

t_hit disk_intersect_ray_collision(const t_ray *ray, t_disk *disk)
{
	t_hit	hit = create_hit(-1.0f, gl_vec3_1f(0.0f), gl_vec3_1f(0.0f));

	// 뒷면을 그리고 싶지 않은 경우 (Backface bulling)
	 if (gl_vec3_dot(gl_vec3_reverse(ray->direction), disk->orientation) < 0.0f) return (hit);

	// 평면과 광선이 수평에 매우 가깝다면 충돌하지 못하는 것으로 판단
	if (abs_float(gl_vec3_dot(ray->direction, disk->orientation)) < 1e-2f) return (hit); // t 계산시 0으로 나누기 방지

	/* 2. 광선과 (무한히 넓은) 평면의 충돌 위치 계산 */
	const float t = (gl_vec3_dot(disk->center, disk->orientation) - gl_vec3_dot(ray->origin, disk->orientation)) / gl_vec3_dot(ray->direction, disk->orientation);

	// 광선의 시작점 이전에 충돌한다면 렌더링할 필요 없음
	if (t < 0.0f) return (hit);

	// 충돌 지점 계산
	hit.distance = t;
	hit.point = gl_vec3_add_vector(ray->origin, gl_vec3_multiply_scalar(ray->direction, t));
	hit.normal = disk->orientation;

//	const t_vec3 tangent = gl_vec3_cross(ray->direction, hit.normal);

	// 충돌 지점이 원 반지름 기준으로 안에 있는지 체크.
	const float hit_to_center = abs_float(gl_vec3_get_magnitude(gl_vec3_subtract_vector(hit.point, disk->center)));
//	const float hit_to_center = gl_vec3_get_magnitude(gl_vec3_subtract_vector(hit.point, disk->center));
//	if (hit_to_center < disk->radius) // 만약 안에 있다면, uv계산.
	if (hit_to_center < disk->radius)
	{

//		// to X-axis of uv plane
//		const t_vec3 bitangent = gl_vec3_cross(tangent, disk->orientation);
//
//		const t_vec3 dx = gl_vec3_multiply_scalar(bitangent, disk->radius);
//		const t_vec3 dy = gl_vec3_multiply_scalar(tangent, disk->radius);

//		const t_vec3 v0 = gl_vec3_subtract_vector(disk->center, gl_vec3_add_vector(dx, dy));
//		const t_vec3 v1 = gl_vec3_add_vector(v0, gl_vec3_multiply_scalar(dy, 2.0f));
//		const t_vec3 v2 = gl_vec3_add_vector(v0, gl_vec3_multiply_scalar(dx, 2.0f));
//		const t_vec3 weights = get_barycentric_coord(v0, v1, v2, hit.point);
//
//		hit.uv = gl_vec2_1f(0.0f);
//		hit.uv = gl_vec2_multiply_scalar(gl_vec2_2f(0.0f, 1.0f), weights.y);
//		hit.uv = gl_vec2_add_vector(hit.uv, gl_vec2_multiply_scalar(gl_vec2_2f(1.0f, 0.0f), weights.z));

		/*   v1 (0.1)
		 *    -------------
		 *    |           |
		 *    |     .     |
		 *    |           |
		 *    -------------
		 *  v0            v2 (1.0)
		 *
		 * */


		return (hit);
	}
	else
		return (create_hit(-1.0f, gl_vec3_1f(0.0f), gl_vec3_1f(0.0f)));
}
