/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_vec3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:48:41 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/08 18:34:43 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_VECTOR3_H
# define GL_VECTOR3_H

# include <math.h>
# include "gl_matrix.h"

typedef union s_vec3 {
	struct {
		float	x;
		float	y;
		float	z;
	};
	float	v[3];
}	t_vec3;

/* Create r-value vec3 and Return. */
extern t_vec3	gl_vec3(float _x, float _y, float _z);

/* returns -v1 (reversed direction) */
extern t_vec3	gl_vec3_reverse(t_vec3 v);

/* returns (v1 + v2) */
extern t_vec3	gl_vec3_add(t_vec3 v1, t_vec3 v2);

/* returns (v1 - v2) */
extern t_vec3	gl_vec3_subtract(t_vec3 v1, t_vec3 v2);

/* Returns min(max(x, minVal), maxVal) for each component
in x using the floating-point values minVal and maxVal. */
extern t_vec3	gl_vec3_clamp(t_vec3 v, t_vec3 min, t_vec3 max);

/* Create Normal Vector */
extern t_vec3	gl_vec3_normalize(t_vec3 v);

/* Returns dot-product result */
extern float	gl_vec3_dot_product(t_vec3 v1, t_vec3 v2);

/* Returns cross-product result
 * FIX: check if cross product code is valid !!! */
extern t_vec3	gl_vec3_cross_product(t_vec3 v1, t_vec3 v2);

/* Returns magnitude result [v.v] */
extern float	gl_vec3_get_magnitude(t_vec3 v);



#endif /* VECTOR3_H */
