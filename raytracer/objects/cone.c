
#include "cone.h"
#include "helper.h"

extern t_hit cone_intersect_ray_collision(const t_ray *ray, t_cone *cone)
{
	t_hit hit = create_hit(-1.0f, gl_vec3_1f(0.0f), gl_vec3_1f(0.0f));
	(void)ray, (void)cone;

	cone->orientation = gl_vec3_normalize(cone->orientation);


	//	[참고]
	//	http://www.illusioncatalyst.com/notes_files/mathematics/line_cone_intersection.php

	const t_vec3 h = cone->orientation;
	const t_vec3 v = ray->direction;
	const t_vec3 H = gl_vec3_add_vector(cone->pos, gl_vec3_multiply_scalar(cone->orientation, cone->height));
	const t_vec3 w = gl_vec3_subtract_vector(ray->origin, H);
	const float m = (cone->radius * cone->radius) / (cone->height * cone->height);

	const float a0 = gl_vec3_dot(v, v);
	const float v_h = gl_vec3_dot(v, h);
	const float v_h_sqrt = v_h * v_h;
	const float a1 = m * v_h_sqrt;
	const float a = a0 - a1 - v_h_sqrt;

	const float b0 = gl_vec3_dot(v, w);
	const float w_h = gl_vec3_dot(w, h);
	const float b1 = v_h * w_h;
	const float b = 2 * (b0 - m * b1 - b1);

	const float c0 = gl_vec3_dot(w, w);
	const float c = c0 - (m * w_h * w_h) - (w_h * w_h);

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
		float c_to_q = gl_vec3_dot(cone->orientation, gl_vec3_subtract_vector(hit.point, cone->pos));
		const t_vec3 q = gl_vec3_add_vector(cone->pos, gl_vec3_multiply_scalar(cone->orientation, c_to_q));

		if (c_to_q < 0.0f)
		{
			return create_hit(-1.0f, gl_vec3_1f(0.0f), gl_vec3_1f(0.0f));
		}
		else if (c_to_q >= cone->height)
		{
			return create_hit(-1.0f, gl_vec3_1f(0.0f), gl_vec3_1f(0.0f));
		}
		else
		{
			hit.normal = gl_vec3_normalize( gl_vec3_subtract_vector(hit.point, q));
		}



	}

	return (hit);
}
