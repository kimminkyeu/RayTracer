/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:54:47 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/19 02:51:39 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "gl_vec3.h"
# include "ray.h"

typedef struct s_plane {
	t_vec3	pos;
	t_vec3	normal;
}	t_plane;

extern t_hit	plane_intersect_ray_collision(const t_ray *ray, \
												t_plane *plane);

#endif /** plane.h */
