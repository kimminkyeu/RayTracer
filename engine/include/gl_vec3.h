/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_vec3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:48:41 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/30 22:56:07 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_VEC3_H
# define GL_VEC3_H

# include <math.h>
# include "gl_matrix.h"

typedef union s_vec3 {
	struct {
		float	x;
		float	y;
		float	z;
	};
	struct {
		float	b;
		float	g;
		float	r;
	};
	float	v[3];
}	t_vec3;

/* Create r-value vec3 and Return. */
extern t_vec3	vec3_3f(float _x_b, float _y_g, float _z_r);

/* Create and Return R-value from single float argument.
- : functions sets every value to (float _k) */
extern t_vec3	vec3_1f(float _k);

/* returns -v1 (reversed direction) */
extern t_vec3	vec3_reverse(t_vec3 v);

/* returns (v1 + v2) */
extern t_vec3	add3(t_vec3 v1, t_vec3 v2);

/* returns (v.x + f, v.y + f, v.z + f).
    - add each component with the given float */
extern t_vec3	add3_f(t_vec3 v, float f);

/* returns (v1 - v2) */
extern t_vec3	sub3(t_vec3 v1, t_vec3 v2);

/* returns (v1 * scalar) */
extern t_vec3	mult3_scalar(t_vec3 v, float scalar);

/** Multiply each element.
 * (v1.x * v2.x, v1.y * v2.y, v3.z * v3.z) */
extern t_vec3	mult3(t_vec3 v1, t_vec3 v2);

/* Returns min(max(x, minVal), maxVal) for each component
in x using the floating-point values minVal and maxVal.
* [clamping is used to restrict a value to a given range]
*/
extern t_vec3	clamp3(t_vec3 v, t_vec3 min, t_vec3 max);

/* Create Normal Vector */
extern t_vec3	normal3(t_vec3 v);

/* Returns dot-product result */
extern float	dot3(t_vec3 v1, t_vec3 v2);

/* Returns cross-product result
 * FIX: check if cross product code is valid !!! */
extern t_vec3	cross3(t_vec3 v1, t_vec3 v2);

/* Returns magnitude result [v.v] */
extern float	len3(t_vec3 v);

#endif /* VECTOR3_H */
