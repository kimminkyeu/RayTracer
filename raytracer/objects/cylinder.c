
# include "ray.h"
# include "helper.h"
# include "cylinder.h"

/** ------------------------------ *
 *  |     Plain hit detection      |
 *  ------------------------------ */
t_hit cylinder_intersect_ray_collision(const t_ray *ray, t_cylinder *cylinder)
{
	(void)ray, (void)cylinder;
	t_hit	hit = create_hit(-1.0f, gl_vec3_1f(0.0f), gl_vec3_1f(0.0f));

	// 충돌 지점 계산
//	hit.point = gl_vec3_add_vector(ray->origin, gl_vec3_multiply_scalar(ray->direction, t));
//	hit.distance = t;
//	hit.normal = plane->normal;

	return (hit);
}
