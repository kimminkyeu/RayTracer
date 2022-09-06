/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_4x4_shear_functions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:34:54 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/05 23:30:48 by sungjpar         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "gl_matrix.h"

/* FIXME : handle matrix accordingly  */
t_mat4x4	gl_mat4x4_shear_x_axis(float degree)
{
	t_mat4x4	mat;

	mat.m[0][0] = 1.0f;
	mat.m[0][1] = tanf(gl_get_radian(degree));
	mat.m[1][1] = 1.0f;
	mat.m[2][2] = 1.0f;
	mat.m[3][3] = 1.0f;
	return (mat);
}

/* FIXME : handle matrix accordingly  */
t_mat4x4	gl_mat4x4_shear_y_axis(float degree)
{
	t_mat4x4	mat;

	mat.m[0][0] = 1.0f;
	mat.m[1][0] = tanf(gl_get_radian(degree));
	mat.m[1][1] = 1.0f;
	mat.m[2][2] = 1.0f;
	mat.m[3][3] = 1.0f;
	return (mat);
}

/* FIXME : handle matrix accordingly  */
t_mat4x4	gl_mat4x4_shear_z_axis(float degree)
{
	t_mat4x4	mat;

	mat.m[0][0] = 1.0f;
	mat.m[1][1] = 1.0f;
	mat.m[2][1] = tanf(gl_get_radian(degree));
	mat.m[2][2] = 1.0f;
	mat.m[3][3] = 1.0f;
	return (mat);
}
