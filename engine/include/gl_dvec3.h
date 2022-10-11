/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_dvec3.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:48:41 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/11 17:13:01 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_VECTOR3_H
# define GL_VECTOR3_H

# include <math.h>
# include "gl_matrix.h"

typedef union s_dvec3 {
	struct {
		double	x;
		double	y;
		double	z;
	};
	struct {
		double	b;
		double	g;
		double	r;
	};
	double	v[3];
}	t_dvec3;

/* Create r-value vec3 and Return. */
extern t_dvec3	gl_dvec3_3d(double _x, double _y, double _z);

/* Create and Return R-value from single double argument.
- : functions sets every value to (double _k) */
extern t_dvec3	gl_dvec3_1d(double _k);

/* returns -v1 (reversed direction) */
extern t_dvec3	gl_dvec3_reverse(t_dvec3 v);

/* returns (v1 + v2) */
extern t_dvec3	gl_dvec3_add_vector(t_dvec3 v1, t_dvec3 v2);

/* returns (v.x + f, v.y + f, v.z + f).
    - add each component with the given double */
extern t_dvec3	gl_dvec3_add_double(t_dvec3 v, double f);

/* returns (v1 - v2) */
extern t_dvec3	gl_dvec3_subtract_vector(t_dvec3 v1, t_dvec3 v2);

/* returns (v1 * scalar) */
extern t_dvec3	gl_dvec3_multiply_scalar(t_dvec3 v, double scalar);

/* Returns min(max(x, minVal), maxVal) for each component
in x using the floating-point values minVal and maxVal.
* [clamping is used to restrict a value to a given range]
*/
extern t_dvec3	gl_dvec3_clamp(t_dvec3 v, t_dvec3 min, t_dvec3 max);

/* Create Normal Vector */
extern t_dvec3	gl_dvec3_normalize(t_dvec3 v);

/* Returns dot-product result */
extern double	gl_dvec3_dot(t_dvec3 v1, t_dvec3 v2);

/* Returns cross-product result
 * FIX: check if cross product code is valid !!! */
extern t_dvec3	gl_dvec3_cross(t_dvec3 v1, t_dvec3 v2);

/* Returns magnitude result [v.v] */
extern double	gl_dvec3_get_magnitude(t_dvec3 v);



#endif /* VECTOR3_H */
