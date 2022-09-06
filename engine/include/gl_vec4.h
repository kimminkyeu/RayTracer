/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_vec4.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:48:41 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/06 16:46:20 by sungjpar         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_VECTOR4_H
# define GL_VECTOR4_H

# include <math.h>
# include "gl_matrix.h"

typedef union s_vec4 {
	struct {
		float	x;
		float	y;
		float	z;
		float	w;
	};
	float	v[4];
}	t_vec4;

/* Create r-value vec4 and Return. */
extern t_vec4	gl_vec4(float _x, float _y, float _z, float _w);

/* Create Normal Vector */
extern t_vec4	gl_vec4_normalize(t_vec4 v);

/* Returns dot-product result */
extern float	gl_vec4_dot_product(t_vec4 v1, t_vec4 v2);

/* Returns cross-product result */
extern t_vec4	gl_vec4_cross_product(t_vec4 v1, t_vec4 v2);

/* Returns magnitude result [v.v] */
extern float	gl_vec4_get_magnitude(t_vec4 v);

/* Returns the result of matrix muliplication with vec4 */
extern t_vec4	gl_vec4_multiply_matrix(t_mat4x4 m, t_vec4 v);

#endif /* VECTOR4_H */
