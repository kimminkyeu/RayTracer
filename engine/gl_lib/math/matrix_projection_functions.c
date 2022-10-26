/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_projection_functions.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:36:38 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 12:14:06 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_matrix.h"

t_mat4x4	gl_parallel(void)
{
	static t_mat4x4	mat;

	mat.m[0][0] = 1.0f;
	mat.m[1][1] = 1.0f;
	mat.m[2][2] = 1.0f;
	mat.m[3][3] = 1.0f;
	return (mat);
}

t_mat4x4	gl_isometric(void)
{
	static t_mat4x4	mat;

	mat = gl_mat4x4_multiply(gl_mat4x4_rotate_y_axis(30.0f), \
								gl_mat4x4_rotate_x_axis(30.0f));
	mat = gl_mat4x4_multiply(gl_mat4x4_rotate_z_axis(30.0f), mat);
	return (mat);
}
