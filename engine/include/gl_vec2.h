/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_vec2.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:23:51 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/08 18:34:56 by minkyeki         ###   ########.fr       */
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
	float	v[2];
}	t_vec2;

/* Create R-value vec2 and returns data */
extern t_vec2	gl_vec2(float _x, float _y);

/* returns -v1 (reversed direction) */
extern t_vec2	gl_vec2_reverse(t_vec2 v);

/* returns (v1 + v2) */
extern t_vec2	gl_vec2_add(t_vec2 v1, t_vec2 v2);

/* returns (v1 - v2) */
extern t_vec2	gl_vec2_subtract(t_vec2 v1, t_vec2 v2);

/* Returns min(max(x, minVal), maxVal) for each component
in x using the floating-point values minVal and maxVal. */
extern t_vec2	gl_vec2_clamp(t_vec2 v, t_vec2 min, t_vec2 max);

extern float	gl_vec2_dot_product(t_vec2 v1, t_vec2 v2);

extern float	gl_vec2_get_magnitude(t_vec2 v);

extern t_vec2	gl_vec2_normalize(t_vec2 v);

#endif /* VECTOR2 */
