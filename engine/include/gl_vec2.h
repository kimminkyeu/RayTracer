/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_vec2.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:23:51 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/14 22:34:30 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_VECTOR2
# define GL_VECTOR2

# include <math.h>

typedef union u_vec2 {
	struct {
		float	x;
		float	y;
	};
	struct
	{
		float	width;
		float	height;
	};
	float	v[2];
}	t_vec2;

/* Create R-value vec2 and returns data */
extern t_vec2	gl_vec2_2f(float _x, float _y);

/* Create and Return R-value from single float argument.
- : functions sets every value to (float _k) */
extern t_vec2	gl_vec2_1f(float _k);

/* returns -v1 (reversed direction) */
extern t_vec2	gl_vec2_reverse(t_vec2 v);

/* returns (v1 + v2) */
extern t_vec2	gl_vec2_add_vector(t_vec2 v1, t_vec2 v2);

/* returns (v.x + f, v.y + f).
    - add each component with the given float */
extern t_vec2	gl_vec2_add_float(t_vec2 v, float f);

/* returns (v1 - v2) */
extern t_vec2	gl_vec2_subtract_vector(t_vec2 v1, t_vec2 v2);

/* returns (v.x + f, v.y + f).
    - add each component with the given float */
extern t_vec2	gl_vec2_subtract_float(t_vec2 v1, float f);

/* returns (v1 * scalar) */
extern t_vec2	gl_vec2_multiply_scalar(t_vec2 v, float scalar);

/* Returns min(max(x, minVal), maxVal) for each component
in x using the floating-point values minVal and maxVal.
* [clamping is used to restrict a value to a given range]
*/
extern t_vec2	gl_vec2_clamp(t_vec2 v, t_vec2 min, t_vec2 max);

extern float	gl_vec2_dot_product(t_vec2 v1, t_vec2 v2);

extern float	gl_vec2_get_magnitude(t_vec2 v);

extern t_vec2	gl_vec2_normalize(t_vec2 v);

#endif /* VECTOR2 */
