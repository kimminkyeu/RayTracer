/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 22:36:44 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/31 16:37:23 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace_ray.h"

/** Reflected ray dir : [ d - 2( n . d )n ]
 *  move ray slightly to it's direction to avoid early hit.
 * */
t_vec3	calculate_reflection(t_device *device, const t_ray *ray, t_hit hit, \
							const int reflection_recursive_level)
{
	const t_vec3	reflected_ray_dir = sub3(ray->direction, \
						(mult3_scalar(mult3_scalar(hit.normal, \
						dot3(ray->direction, hit.normal)), 2.0f)));
	const t_vec3	hit_point_offset = add3(hit.point, \
						mult3_scalar(reflected_ray_dir, 0.001f));
	const t_ray		reflected_ray = create_ray(hit_point_offset, \
						reflected_ray_dir);
	const t_vec3	reflected_color = trace_ray(device, \
						&reflected_ray, reflection_recursive_level - 1);

	return (mult3_scalar(reflected_color, hit.obj->material.reflection));
}
