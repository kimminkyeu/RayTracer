/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:54:40 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/14 15:23:54 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

// # include "gl_vec3.h"
// # include "gl_vec2.h"
# include "ray.h"

typedef struct s_triangle {
	t_vec3	v0; // vertex_1
	t_vec3	v1; // vertex_2
	t_vec3	v2;	// vertex_3

	t_vec2 uv0; // for texture
	t_vec2 uv1; // for texture
	t_vec2 uv2; // for texture

}	t_triangle;

extern t_hit triangle_intersect_ray_collision(t_ray *ray, t_triangle *triangle);

#endif /** Triangle_h */
