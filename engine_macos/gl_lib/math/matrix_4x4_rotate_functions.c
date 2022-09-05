/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_4x4_rotate_functions.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 23:10:50 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/05 23:31:20 by sungjpar         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "gl_matrix.h"

t_mat4x4	gl_mat4x4_rotate_x_axis(float _degree)
{
	static t_mat4x4	mat;

	mat.m[0][0] = 1.0f;
	mat.m[1][1] = cosf(gl_get_radian(_degree));
	mat.m[1][2] = -sinf(gl_get_radian(_degree));
	mat.m[2][1] = sinf(gl_get_radian(_degree));
	mat.m[2][2] = cosf(gl_get_radian(_degree));
	mat.m[3][3] = 1.0f;
	return (mat);
}

t_mat4x4	gl_mat4x4_rotate_y_axis(float _degree)
{
	static t_mat4x4	mat;

	mat.m[0][0] = cosf(gl_get_radian(_degree));
	mat.m[0][2] = -sinf(gl_get_radian(_degree));
	mat.m[1][1] = 1.0f;
	mat.m[2][0] = sinf(gl_get_radian(_degree));
	mat.m[2][2] = cosf(gl_get_radian(_degree));
	mat.m[3][3] = 1.0f;
	return (mat);
}

t_mat4x4	gl_mat4x4_rotate_z_axis(float _degree)
{
	static t_mat4x4	mat;

	mat.m[0][0] = cosf(gl_get_radian(_degree));
	mat.m[0][1] = -sinf(gl_get_radian(_degree));
	mat.m[1][0] = sinf(gl_get_radian(_degree));
	mat.m[1][1] = cosf(gl_get_radian(_degree));
	mat.m[2][2] = 1.0f;
	mat.m[3][3] = 1.0f;
	return (mat);
}

