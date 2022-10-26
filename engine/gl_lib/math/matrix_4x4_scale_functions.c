/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_4x4_scale_functions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 23:13:06 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 12:02:37 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_matrix.h"

/* scale from (0.0) */
t_mat4x4	gl_mat4x4_scale_from_origin(float _scale_rate)
{
	static t_mat4x4	mat;

	mat.m[0][0] = _scale_rate;
	mat.m[1][1] = _scale_rate;
	mat.m[2][2] = _scale_rate;
	mat.m[3][3] = 1.0f;
	return (mat);
}

/* sclae from (x, y, z) */
t_mat4x4	gl_mat4x4_scale_from_point(float _x, float _y, float _z, \
										float _scale_rate)
{
	static t_mat4x4	mat;

	mat = gl_mat4x4_multiply(gl_mat4x4_scale_from_origin(_scale_rate), \
			gl_mat4x4_translate(-_x, -_y, -_z));
	mat = gl_mat4x4_multiply(gl_mat4x4_translate(_x, _y, _z), mat);
	return (mat);
}
