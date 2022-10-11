/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_dvec4.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:48:41 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/11 18:23:24 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_DVECTOR4_H
# define GL_DVECTOR4_H

# include <math.h>
# include "gl_matrix.h"

/* Typedef for Homogeneous-Coordinate-System.
 * NOTE: (1) data is direction-vector if w is 0.0f.
 * NOTE: (2) data is point if w is 1.0f.
 * */

typedef union s_dvec4 {
	struct {
		double	x;
		double	y;
		double	z;
		double	w;
	};
	struct {
		double	b; // blue
		double	g; // green
		double	r; // red
		double	a; // alpha
	};
	double	v[4];
}	t_dvec4;

/* Create r-value vec4 and Return.
NOTE: you can use vec4 for color system in reversed order. (int argb)*/
extern t_dvec4	gl_dvec4_4d(double x_or_b, double y_or_g, double z_or_r, double w_or_a);

/* Create and Return R-value from single double argument.
- : functions sets every value to (double _k) */
extern t_dvec4	gl_dvec4_1d(double _k);

/* returns -v1 (reversed direction) */
extern t_dvec4	gl_dvec4_reverse(t_dvec4 v);

/* returns (v1 + v2) */
extern t_dvec4	gl_dvec4_add_vector(t_dvec4 v1, t_dvec4 v2);

/* returns (v.x + f, v.y + f, v.z + f, v.w + f).
    - add each component with the given double */
extern t_dvec4	gl_dvec4_add_double(t_dvec4 v, double d);

/* returns (v1 - v2) */
extern t_dvec4	gl_dvec4_subtract_vector(t_dvec4 v1, t_dvec4 v2);

/* returns (v1 * scalar) */
extern t_dvec4	gl_dvec4_multiply_scalar(t_dvec4 v, double scalar);

/* Returns min(max(x, minVal), maxVal) for each component
in x using the floating-point values minVal and maxVal.
* [clamping is used to restrict a value to a given range]
*/
extern t_dvec4	gl_dvec4_clamp(t_dvec4 v, t_dvec4 min, t_dvec4 max);

/* Create Normal Vector */
extern t_dvec4	gl_dvec4_normalize(t_dvec4 v);

/* Returns dot-product result */
extern double	gl_dvec4_dot(t_dvec4 v1, t_dvec4 v2);

/* Returns cross-product result.
 * FIX: check if cross product code is valid !!! */
extern t_dvec4	gl_dvec4_cross(t_dvec4 v1, t_dvec4 v2);

/* Returns magnitude result [v.v] */
extern double	gl_dvec4_get_magnitude(t_dvec4 v);

/* Returns the result of matrix multiplication with vec4 */
extern t_dvec4	gl_dvec4_multiply_matrix(t_mat4x4 m, t_dvec4 v);

#endif /* VECTOR4_H */
