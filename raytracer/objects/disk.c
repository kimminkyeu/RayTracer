/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 01:14:11 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/31 15:33:58 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disk.h"
#include "ray.h"

static bool	is_backface(const t_ray *ray, t_disk *disk)
{
	if (dot3(vec3_reverse(ray->direction), disk->orientation) < 0.0f)
		return (true);
	else
		return (false);
}

static bool	is_ray_horizontal_to_surface(const t_ray *ray, t_disk *disk)
{
	if (abs_float(dot3(ray->direction, disk->orientation)) < 0.001f)
		return (true);
	else
		return (false);
}

t_hit	disk_intersect_ray_collision(const t_ray *ray, t_disk *disk)
{
	t_hit	hit;
	float	t;
	float	hit_to_center;

	hit = create_hit(-1.0f, vec3_1f(0.0f), vec3_1f(0.0f));
	if (is_backface(ray, disk) || is_ray_horizontal_to_surface(ray, disk))
		return (hit);
	t = (dot3(disk->center, disk->orientation) \
 - dot3(ray->origin, disk->orientation)) \
 / dot3(ray->direction, disk->orientation);
	if (t < 0.0f)
		return (hit);
	hit.distance = t;
	hit.point = add3(ray->origin, \
        mult3_scalar(ray->direction, t));
	hit.normal = disk->orientation;
	hit_to_center = abs_float(len3(\
                sub3(hit.point, disk->center)));
	if (hit_to_center < disk->radius)
		return (hit);
	else
		return (create_hit(-1.0f, vec3_1f(0.0f), vec3_1f(0.0f)));
}
