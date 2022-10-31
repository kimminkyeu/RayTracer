/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_vec2.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:23:51 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 11:54:15 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_VEC2_H
# define GL_VEC2_H

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
extern t_vec2	vec2_2f(float _x, float _y);

/* Create and Return R-value from single float argument.
- : functions sets every value to (float _k) */
extern t_vec2	vec2_1f(float _k);

/* returns -v1 (reversed direction) */
extern t_vec2	vec2_reverse(t_vec2 v);

/* returns (v1 + v2) */
extern t_vec2	add2(t_vec2 v1, t_vec2 v2);

/* returns (v.x + f, v.y + f).
    - add each component with the given float */
extern t_vec2	add2_f(t_vec2 v, float f);

/* returns (v1 - v2) */
extern t_vec2	sub2(t_vec2 v1, t_vec2 v2);

/* returns (v.x + f, v.y + f).
    - add each component with the given float */
extern t_vec2	sub2_f(t_vec2 v1, float f);

/* returns (v1 * scalar) */
extern t_vec2	mult2_scalar(t_vec2 v, float scalar);

/* Returns min(max(x, minVal), maxVal) for each component
in x using the floating-point values minVal and maxVal.
* [clamping is used to restrict a value to a given range]
*/
extern t_vec2	clamp2(t_vec2 v, t_vec2 min, t_vec2 max);

extern float	dot2(t_vec2 v1, t_vec2 v2);

extern float	len2(t_vec2 v);

extern t_vec2	normal2(t_vec2 v);

#endif /* VECTOR2 */
