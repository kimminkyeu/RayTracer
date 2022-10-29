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

typedef struct s_cylinder {
	t_vec3	pos;
	t_vec3	orientation;
	float	radius;
	float	height;
}	t_cylinder;

extern t_hit	cylinder_intersect_ray_collision(const t_ray *ray, t_cylinder *cylinder);

#endif /** cylinder.h */
