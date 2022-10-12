/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:42:24 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/12 17:29:02 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

#include "gl_vec3.h"
#include "hit.h"

typedef struct s_ray {
	t_vec3	origin; // ray origin
	t_vec3	direction; // ray direction
}	t_ray;

extern t_ray create_ray(t_vec3 origin, t_vec3 direction);

extern t_hit sphere_intersect_ray_collision(t_ray *ray, t_sphere *sphere);
extern t_hit triangle_intersect_ray_collision(t_ray *ray, t_triangle *triangle);
extern t_hit square_intersect_ray_collision(t_ray *ray, t_sphere *sphere);
extern t_hit plain_intersect_ray_collision(t_ray *ray, t_sphere *sphere);

#endif /** Ray.h */
