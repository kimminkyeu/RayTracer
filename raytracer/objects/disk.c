/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 01:14:11 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/31 01:23:07 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disk.h"
#include "ray.h"

static bool	is_backface(const t_ray *ray, t_disk *disk)
{
	if (gl_vec3_dot(gl_vec3_reverse(ray->direction), disk->orientation) < 0.0f)
		return (true);
	else
		return (false);
}

static bool	is_ray_horizontal_to_surface(const t_ray *ray, t_disk *disk)
{
	if (abs_float(gl_vec3_dot(ray->direction, disk->orientation)) < 1e-2f)
		return (true);
	else
		return (false);
}

t_hit disk_intersect_ray_collision(const t_ray *ray, t_disk *disk)
{
	t_hit	hit;
	float	t;
	float	hit_to_center;

	hit = create_hit(-1.0f, gl_vec3_1f(0.0f), gl_vec3_1f(0.0f));
	if (is_backface(ray, disk) || is_ray_horizontal_to_surface(ray, disk))
		return (hit);
	t = (gl_vec3_dot(disk->center, disk->orientation) - gl_vec3_dot(ray->origin, disk->orientation)) / gl_vec3_dot(ray->direction, disk->orientation);
	if (t < 0.0f)
		return (hit);
	hit.distance = t;
	hit.point = gl_vec3_add_vector(ray->origin, gl_vec3_multiply_scalar(ray->direction, t));
	hit.normal = disk->orientation;
	hit_to_center = abs_float(gl_vec3_get_magnitude(gl_vec3_subtract_vector(hit.point, disk->center)));
	if (hit_to_center < disk->radius)
		return (hit);
	else
		return (create_hit(-1.0f, gl_vec3_1f(0.0f), gl_vec3_1f(0.0f)));
}
