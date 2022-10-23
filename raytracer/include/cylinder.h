/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:03:49 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/22 22:55:27 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "gl_vec3.h"

//#    pos              orientation       diameter   height      diffuse color
//cy   50.0,0.0,20.6    0.0,0.0,1.0        14.2      21.42       10,0,255

typedef struct s_cylinder {
	t_vec3	pos; // 바닥 지점
	t_vec3	orientation;
	float	radius; // 반지름
	float	height; // 높이
}	t_cylinder;

extern t_hit cylinder_intersect_ray_collision(const t_ray *ray, t_cylinder *cylinder);

#endif /** cylinder.h */
