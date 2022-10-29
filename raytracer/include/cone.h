/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:03:20 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/14 15:03:39 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H

# include "hit.h"
# include "ray.h"

typedef struct s_cone {
	t_vec3	pos;
	t_vec3	orientation;
	float	radius;
	float	height;
}	t_cone;

extern t_hit	cone_intersect_ray_collision(const t_ray *ray, t_cone *cone);

#endif /** cone.h */
