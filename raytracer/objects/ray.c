/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:12:52 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/31 17:46:16 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "hit.h"

t_ray	create_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_hit	create_hit(float distance, t_vec3 normal, t_vec3 point)
{
	t_hit	hit;

	hit.distance = distance;
	hit.normal = normal;
	hit.point = point;
	return (hit);
}

// 물체의 타입에 따라 다르게 체크.
t_hit	check_ray_collision(const t_ray *ray, t_object *obj)
{
	if (obj->type == TYPE_SPHERE)
		return (sphere_intersect_ray_collision(ray, obj->obj_data));
	else if (obj->type == TYPE_PLANE)
		return (plane_intersect_ray_collision(ray, obj->obj_data));
	else if (obj->type == TYPE_CYLINDER)
		return (cylinder_intersect_ray_collision(ray, obj->obj_data));
	else if (obj->type == TYPE_CONE)
		return (cone_intersect_ray_collision(ray, obj->obj_data));
	return (create_hit(-1.0f, vec3_1f(0.0f), vec3_1f(0.0f)));
}
