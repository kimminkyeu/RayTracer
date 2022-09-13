/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_vec4.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:48:41 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/13 13:29:33 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_VECTOR4_H
# define GL_VECTOR4_H

# include <math.h>
# include "gl_matrix.h"

/* Typedef for Homogeneous-Coordinate-System.
 * NOTE: (1) data is direction-vector if w is 0.0f.
 * NOTE: (2) data is point if w is 1.0f.
 * */

typedef union s_vec4 {
	struct {
		float	x;
		float	y;
		float	z;
		float	w;
	};
	struct {
		float	b; // blue
		float	g; // green
		float	r; // red
		float	a; // alpha
	};
	float	v[4];
}	t_vec4;

/* Create r-value vec4 and Return.
NOTE: you can use vec4 for color system in reversed order. (int argb)*/
extern t_vec4	gl_vec4(float x_or_b, float y_or_g, float z_or_r, float w_or_a);

/* Create and Return R-value from single float argument.
- : functions sets every value to (float _k) */
extern t_vec4	gl_vec4_(float _k);

/* returns -v1 (reversed direction) */
extern t_vec4	gl_vec4_reverse(t_vec4 v);

/* returns (v1 + v2) */
extern t_vec4	gl_vec4_add_vector(t_vec4 v1, t_vec4 v2);

/* returns (v.x + f, v.y + f, v.z + f, v.w + f).
    - add each component with the given float */
extern t_vec4	gl_vec4_add_float(t_vec4 v, float f);

/* returns (v1 - v2) */
extern t_vec4	gl_vec4_subtract_vector(t_vec4 v1, t_vec4 v2);

/* returns (v1 * scalar) */
extern t_vec4	gl_vec4_multiply_scalar(t_vec4 v, float scalar);

/* Returns min(max(x, minVal), maxVal) for each component
in x using the floating-point values minVal and maxVal.
* [clamping is used to restrict a value to a given range]
*/
extern t_vec4	gl_vec4_clamp(t_vec4 v, t_vec4 min, t_vec4 max);

/* Create Normal Vector */
extern t_vec4	gl_vec4_normalize(t_vec4 v);

/* Returns dot-product result */
extern float	gl_vec4_dot_product(t_vec4 v1, t_vec4 v2);

/* Returns cross-product result.
 * FIX: check if cross product code is valid !!! */
extern t_vec4	gl_vec4_cross_product(t_vec4 v1, t_vec4 v2);

/* Returns magnitude result [v.v] */
extern float	gl_vec4_get_magnitude(t_vec4 v);

/* Returns the result of matrix multiplication with vec4 */
extern t_vec4	gl_vec4_multiply_matrix(t_mat4x4 m, t_vec4 v);

#endif /* VECTOR4_H */
