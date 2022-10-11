/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_dvec2.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:23:51 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/11 17:13:14 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_VECTOR2
# define GL_VECTOR2

# include <math.h>

typedef union u_dvec2 {
	struct {
		double	x;
		double	y;
	};
	struct
	{
		double	width;
		double	height;
	};
	double	v[2];
}	t_dvec2;

/* Create R-value vec2 and returns data */
extern t_dvec2	gl_dvec2_2d(double _x, double _y);

/* Create and Return R-value from single float argument.
- : functions sets every value to (float _k) */
extern t_dvec2	gl_dvec2_1d(double _k);

/* returns -v1 (reversed direction) */
extern t_dvec2	gl_dvec2_reverse(t_dvec2 v);

/* returns (v1 + v2) */
extern t_dvec2	gl_dvec2_add_vector(t_dvec2 v1, t_dvec2 v2);

/* returns (v.x + f, v.y + f).
    - add each component with the given float */
extern t_dvec2	gl_dvec2_add_double(t_dvec2 v, double d);

/* returns (v1 - v2) */
extern t_dvec2	gl_dvec2_subtract_vector(t_dvec2 v1, t_dvec2 v2);

/* returns (v.x + f, v.y + f).
    - add each component with the given float */
extern t_dvec2	gl_dvec2_subtract_float(t_dvec2 v1, double d);

/* returns (v1 * scalar) */
extern t_dvec2	gl_dvec2_multiply_scalar(t_dvec2 v, double scalar);

/* Returns min(max(x, minVal), maxVal) for each component
in x using the floating-point values minVal and maxVal.
* [clamping is used to restrict a value to a given range]
*/
extern t_dvec2	gl_dvec2_clamp(t_dvec2 v, t_dvec2 min, t_dvec2 max);

extern double	gl_dvec2_dot(t_dvec2 v1, t_dvec2 v2);

extern double	gl_dvec2_get_magnitude(t_dvec2 v);

extern t_dvec2	gl_dvec2_normalize(t_dvec2 v);

#endif /* VECTOR2 */
