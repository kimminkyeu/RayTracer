/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 01:23:31 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/31 15:32:45 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_vec3.h"
#include "hit.h"
#include "ray.h"
#include "helper.h"
#include "cylinder.h"
#include "disk.h"

/** ------------------------------ *
 *  |     Plain hit detection      |
 *  ------------------------------ *
 * http://www.illusioncatalyst.com/notes_files/mathematics/
 * line_cylinder_intersection.php
 *
 * */

#define PI	(3.141592)

/** Redturn determinant, d1, d2 */
static t_vec3	calculate_determinant_d1_d2(
		const t_ray *ray, t_cylinder *cylinder)
{
	const t_vec3	omc
		= sub3(ray->origin, cylinder->pos);
	const float		a
		= 1.0f - powf(dot3(ray->direction, cylinder->orientation), 2.0f);
	const float		b2
		= dot3(omc, cylinder->orientation);
	const float		b
		= 2.0f * (dot3(ray->direction, omc)
			- (dot3(ray->direction, cylinder->orientation) * b2));
	float			d[3];

	d[0] = b * b - (4.0f * a * (dot3(omc, omc) - b2 * b2 - cylinder->radius));
	d[1] = (-b - sqrtf(d[0])) / (2.0f * a);
	d[2] = (-b + sqrtf(d[0])) / (2.0f * a);
	return (vec3_3f(d[0], d[1], d[2]));
}

static t_hit	check_bottom_disk(const t_ray *ray, t_cylinder *cylinder)
{
	t_disk	bottom_disk;

	bottom_disk.center = cylinder->pos;
	bottom_disk.orientation = vec3_reverse(cylinder->orientation);
	bottom_disk.radius = cylinder->radius;
	return (disk_intersect_ray_collision(ray, &bottom_disk));
}

static t_hit	check_top_disk(const t_ray *ray, t_cylinder *cylinder)
{
	const t_vec3	top_center = add3(cylinder->pos, \
            mult3_scalar(cylinder->orientation, cylinder->height));
	t_disk			top_disk;

	top_disk.center = top_center;
	top_disk.orientation = cylinder->orientation;
	top_disk.radius = cylinder->radius;
	return (disk_intersect_ray_collision(ray, &top_disk));
}

/** set hit.normal, and tangent for texture */
static void	calculate_cylinder_normal(const t_ray *ray, t_hit *hit, \
										t_cylinder *cylinder, float c_to_q)
{
	const t_vec3	q = add3(cylinder->pos, \
                mult3_scalar(cylinder->orientation, c_to_q));
	const t_vec3	d = vec3_reverse(hit->normal);

	hit->normal = normal3(sub3(hit->point, q));
	hit->uv.x = atan2(d.x, d.z) / (2 * PI) + 0.5f;
	hit->uv.y = (c_to_q / cylinder->height);
	hit->tangent = cross3(ray->direction, hit->normal);
}

t_hit	cylinder_intersect_ray_collision(const t_ray *ray, t_cylinder *cylinder)
{
	t_hit	hit;
	t_vec3	cal_v;
	float	c_to_q;

	hit = create_hit(-1.0f, vec3_1f(0.0f), vec3_1f(0.0f));
	cal_v = calculate_determinant_d1_d2(ray, cylinder);
	if (cal_v.v[0] >= 0.0f)
	{
		hit.distance = min_float(cal_v.v[1], cal_v.v[2]);
		if (hit.distance < 0.0f)
			hit.distance = max_float(cal_v.v[1], cal_v.v[2]);
		hit.point = add3(ray->origin, \
            mult3_scalar(ray->direction, hit.distance));
		c_to_q = dot3(cylinder->orientation, \
            sub3(hit.point, cylinder->pos));
		if (c_to_q <= 0)
			return (check_bottom_disk(ray, cylinder));
		else if (c_to_q >= cylinder->height)
			return (check_top_disk(ray, cylinder));
		else
			calculate_cylinder_normal(ray, &hit, cylinder, c_to_q);
	}
	return (hit);
}
