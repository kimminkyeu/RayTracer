/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:55:47 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/19 02:51:22 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "ray.h"

typedef struct s_sphere {
	t_vec3	center;
	float	radius;
}	t_sphere;

extern t_hit sphere_intersect_ray_collision(const t_ray *ray, t_sphere *sphere);

#endif /** sphere.h */
