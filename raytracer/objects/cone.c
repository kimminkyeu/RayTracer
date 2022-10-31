/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 23:28:13 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/31 15:16:38 by minkyeki         ###   ########.fr       */
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
	const t_vec3	w = sub3(ray->origin,
			add3(cone->pos, mult3_scalar(cone->orientation, cone->height)));
	const float		m
		= (cone->radius * cone->radius) / (cone->height * cone->height);
	const float		v_h = dot3(ray->direction, cone->orientation);
	const float		w_h = dot3(w, cone->orientation);
	float			d[4];

	d[0] = dot3(ray->direction, ray->direction) - (m * v_h * v_h) - v_h * v_h;
	d[1] = 2 * (dot3(ray->direction, w) - m * (v_h * w_h) - (v_h * w_h));
	d[2] = dot3(w, w) - (m * w_h * w_h) - (w_h * w_h);
	d[3] = d[1] * d[1] - (4.0f * d[0] * d[2]);
	return (
		vec3_3f(d[3], (-d[1] - sqrtf(d[3]))
			/ (2.0f * d[0]), (-d[1] + sqrtf(d[3])) / (2.0f * d[0])));
}

/** [ Calculating cone object collision ]
 *
 * (1) How to calcalate cone intersection.
 * http://www.illusioncatalyst.com/notes_files/mathematics
 * /line_cone_intersection.php
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

static void	calculate_cone_normal(t_hit *hit, t_cone *cone, t_vec3 q)
{
	const t_vec3	y_dir = cone->orientation;
	const t_vec3	x_dir = normal3(sub3(hit->point, q));
	const t_vec3	x_vec = mult3_scalar(x_dir, cone->height);
	const t_vec3	y_vec = mult3_scalar(y_dir, cone->radius);
	const t_vec3	normal = normal3(add3(x_vec, y_vec));

	hit->normal = normal;
}

static t_hit	check_bottom_disk(const t_ray *ray, t_cone *cone)
{
	t_disk	bottom_disk;

	bottom_disk.center = cone->pos;
	bottom_disk.orientation = vec3_reverse(cone->orientation);
	bottom_disk.radius = cone->radius;
	return (disk_intersect_ray_collision(ray, &bottom_disk));
}

/** Problem : if camera or light ray is at top of the cone... */
t_hit	cone_intersect_ray_collision(const t_ray *ray, t_cone *cone)
{
	t_hit	hit;
	t_vec3	cal_v;
	float	c_to_q;
	t_vec3	q;

	hit = create_hit(-1.0f, vec3_1f(0.0f), vec3_1f(0.0f));
	cal_v = calculate_determinant_d1_d2(ray, cone);
	if (cal_v.v[0] <= 0.0f)
		return (hit);
	hit.distance = min_float(cal_v.v[1], cal_v.v[2]);
	if (hit.distance < 0.0f)
		hit.distance = max_float(cal_v.v[1], cal_v.v[2]);
	hit.point = add3(ray->origin, mult3_scalar(ray->direction, hit.distance));
	c_to_q = dot3(cone->orientation, sub3(hit.point, cone->pos));
	q = add3(cone->pos, mult3_scalar(cone->orientation, c_to_q));
	if (c_to_q < 0.0f)
		return (check_bottom_disk(ray, cone));
	else if (c_to_q >= cone->height)
		return (create_hit(-1.0f, vec3_1f(0.0f), vec3_1f(0.0f)));
	else
		calculate_cone_normal(&hit, cone, q);
	return (hit);
}
