/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:54:40 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/30 23:14:43 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

# include "ray.h"

typedef struct s_triangle {
	t_vec3	v0;
	t_vec3	v1;
	t_vec3	v2;
	t_vec2	uv0;
	t_vec2	uv1;
	t_vec2	uv2;
}	t_triangle;

extern t_hit		triangle_intersect_ray_collision(const t_ray *ray, \
													t_triangle *triangle);

extern t_triangle	create_triangle(t_vec3 v0, t_vec3 v1, t_vec3 v2);

#endif /** Triangle_h */
