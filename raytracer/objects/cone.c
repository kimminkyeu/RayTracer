/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 23:28:13 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/31 01:41:01 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cone.h"
#include "gl_vec3.h"
#include "gl_vec4.h"
#include "helper.h"
#include "disk.h"

static t_vec3	calculate_determinant_d1_d2(const t_ray *ray, t_cone *cone)
{
	const t_vec3	w = gl_vec3_subtract_vector(ray->origin, gl_vec3_add_vector(cone->pos, gl_vec3_multiply_scalar(cone->orientation, cone->height)));
	const float		m = (cone->radius * cone->radius) / (cone->height * cone->height);
	const float 	v_h = gl_vec3_dot(ray->direction, cone->orientation);
	const float 	w_h = gl_vec3_dot(w, cone->orientation);
	float			d[4];

	d[0] = gl_vec3_dot(ray->direction, ray->direction) - (m * v_h * v_h) - v_h * v_h;
	d[1] = 2 * (gl_vec3_dot(ray->direction, w) - m * (v_h * w_h) - (v_h * w_h));
	d[2] = gl_vec3_dot(w, w) - (m * w_h * w_h) - (w_h * w_h);
	d[3] = d[1] * d[1] - (4.0f * d[0] * d[2]);
	return (gl_vec3_3f(d[3], (-d[1] - sqrtf(d[3])) / (2.0f * d[0]), (-d[1] + sqrtf(d[3])) / (2.0f * d[0])));
}

/** [ Calculating cone object collision ]
 *
 * (1) How to calcalate cone intersection.
 * http://www.illusioncatalyst.com/notes_files/mathematics/line_cone_intersection.php
 *
 * (2) How to calcaulate cone normal
 * Height Radius --> reversed triangle
 *             .
 *            /.                 *
 *          /  .                 .   *.
 *        /    . H     =>     R  .       *.
 *      /      .                 .            *.
 *    /        .                 .________________*.
 *  /__________.                        H
 *       R
*/

t_vec3	calculate_cone_normal(t_hit hit, t_cone *cone, t_vec3 q)
{
	t_vec3 x_dir = gl_vec3_normalize(gl_vec3_subtract_vector(hit.point, q));
    t_vec3 y_dir = cone->orientation;
    t_vec3 x_vec = gl_vec3_multiply_scalar(x_dir, cone->height);
    t_vec3 y_vec = gl_vec3_multiply_scalar(y_dir, cone->radius);
    t_vec3 normal = gl_vec3_normalize(gl_vec3_add_vector(x_vec, y_vec));

	return (normal);
}

t_hit	check_bottom_disk(const t_ray *ray, t_cone *cone)
{
	t_disk	bottom_disk;

	bottom_disk.center = cone->pos;
	bottom_disk.orientation = gl_vec3_reverse(cone->orientation);
	bottom_disk.radius = cone->radius;
	return (disk_intersect_ray_collision(ray, &bottom_disk));
}

t_hit	cone_intersect_ray_collision(const t_ray *ray, t_cone *cone)
{
	t_hit	hit;
	t_vec3	calcauted_values;
	float	c_to_q;
	t_vec3	q;

	hit = create_hit(-1.0f, gl_vec3_1f(0.0f), gl_vec3_1f(0.0f));
	calcauted_values = calculate_determinant_d1_d2(ray, cone);
	if (calcauted_values.v[0] >= 0.0f)
	{
		hit.distance = min_float(calcauted_values.v[1], calcauted_values.v[2]);
		if (hit.distance < 0.0f)
			hit.distance = max_float(calcauted_values.v[1], calcauted_values.v[2]);
		hit.point = gl_vec3_add_vector(ray->origin, gl_vec3_multiply_scalar(ray->direction, hit.distance));
		c_to_q = gl_vec3_dot(cone->orientation, gl_vec3_subtract_vector(hit.point, cone->pos));
		q = gl_vec3_add_vector(cone->pos, gl_vec3_multiply_scalar(cone->orientation, c_to_q));
		if (c_to_q < 0.0f)
			return (check_bottom_disk(ray, cone));
		else if (c_to_q >= cone->height)
			return (create_hit(-1.0f, gl_vec3_1f(0.0f), gl_vec3_1f(0.0f)));
		else
			hit.normal = calculate_cone_normal(hit, cone, q);
	}
	return (hit);
}



