/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:21:00 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/31 17:44:43 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "helper.h"
#include "plane.h"

/** ------------------------------ *
 *  |     Plain hit detection      |
 *  ------------------------------ */
t_hit	plane_intersect_ray_collision(const t_ray *ray, t_plane *plane)
{
	t_hit	hit;
	float	t;

	hit = create_hit(-1.0f, vec3_1f(0.0f), vec3_1f(0.0f));
	if (dot3(vec3_reverse(ray->direction), plane->normal) < 0.0f)
		return (hit);
	if (abs_float(dot3(ray->direction, plane->normal)) < 0.00001f)
		return (hit);
	t = (dot3(plane->pos, plane->normal)
			- dot3(ray->origin, plane->normal))
		/ dot3(ray->direction, plane->normal);
	if (t < 0.0f)
		return (hit);
	hit.point = add3(ray->origin, mult3_scalar(ray->direction, t));
	hit.distance = t;
	hit.normal = plane->normal;
	return (hit);
}
