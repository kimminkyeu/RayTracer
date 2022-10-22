
#include "disk.h"
#include "gl_vec3.h"
#include "hit.h"
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

	// 참고 : http://www.illusioncatalyst.com/notes_files/mathematics/line_cylinder_intersection.php

	// (0) Lowest Point (하단 TOP)
	const t_vec3 bottom_center = cylinder->pos;
	// (1) Highest Point (상단 TOP)
	// : top_center = cylinder->pos + cylinder->height * cylinder->orientation;
	const t_vec3 top_center = gl_vec3_add_vector(bottom_center, gl_vec3_multiply_scalar(cylinder->orientation, cylinder->height));

	// (2) 중심점 normal. (가운데 축. 혹시 normal이 안되있을 수도 있으니 한번 해준다.)
	const t_vec3 axis_dir = gl_vec3_normalize(cylinder->orientation);

	// v is ray_direction.
	// w(=omc) is (ray_start - obj.center).
	const t_vec3 omc = gl_vec3_subtract_vector(ray->origin, bottom_center);
	const float a = 1.0f - powf(gl_vec3_dot(ray->direction, axis_dir), 2.0f);

	// h is axis_dir
	// for b
	const float b0 = gl_vec3_dot(ray->direction, omc);
	const float b1 = gl_vec3_dot(ray->direction, axis_dir);
	const float b2 = gl_vec3_dot(omc, axis_dir);
	const float b = 2.0f * (b0 - (b1 * b2));
	const float c = gl_vec3_dot(omc, omc) - b2 * b2 - cylinder->radius;


	// get determinant
	const float determinant = b * b - (4.0f * a * c);

	if (determinant >= 0.0f)
	{
		const float d1 = (-b - sqrtf(determinant)) / (2.0f * a);
		const float d2 = (-b + sqrtf(determinant)) / (2.0f * a);

		hit.distance = min_float(d1, d2);
		// 투명한 물체라서 빛이 통과시
		if (hit.distance < 0.0f)
			hit.distance = max_float(d1, d2);

		// normal is from q to p, normalized
		hit.point = gl_vec3_add_vector(ray->origin, gl_vec3_multiply_scalar(ray->direction, hit.distance));

		const float c_to_q = gl_vec3_dot(cylinder->orientation, gl_vec3_subtract_vector(hit.point, bottom_center));
		const t_vec3 q = gl_vec3_add_vector(bottom_center, gl_vec3_multiply_scalar(axis_dir, c_to_q));
		hit.normal = gl_vec3_normalize( gl_vec3_subtract_vector(hit.point, q));

		// *  TODO:  set uv later.


		// if is lower or higher than it's height
		// check top and bottom disk.
		(void)top_center;
		if (c_to_q < 0)
		{
			t_disk bottom_disk;
			bottom_disk.center = bottom_center;
			bottom_disk.orientation = gl_vec3_reverse(cylinder->orientation);
			bottom_disk.radius = cylinder->radius;
			return (disk_intersect_ray_collision(ray, &bottom_disk));
		}
		if (c_to_q > cylinder->height)
		{
			t_disk top_disk;
			top_disk.center = top_center;
			top_disk.orientation = cylinder->orientation;
			top_disk.radius = cylinder->radius;
			return (disk_intersect_ray_collision(ray, &top_disk));
			// return (create_hit(-1.0f, gl_vec3_1f(0.0f), gl_vec3_1f(0.0f)));
		}
	}



	return (hit);
}
