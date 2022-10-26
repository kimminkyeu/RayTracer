/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_matrix.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:37:28 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 11:52:40 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_MATRIX_H
# define GL_MATRIX_H

# include <math.h>

/** NOTE: Matrix 4x4 */
typedef struct s_mat4x4 {
	float	m[4][4];
}	t_mat4x4;

extern float	gl_get_radian(float _degree);

/* multiply two matrices and returns result
 * FIX: need faster code! */
extern t_mat4x4	gl_mat4x4_multiply(t_mat4x4 _m1, t_mat4x4 _m2);

/* translate on x-axis or y-axis or z-axis */
extern t_mat4x4	gl_mat4x4_translate(float _x, float _y, float _z);

/* rotate on x-axis or y-axis or z-axis */
extern t_mat4x4	gl_mat4x4_rotate_x_axis(float _degree);
extern t_mat4x4	gl_mat4x4_rotate_y_axis(float _degree);
extern t_mat4x4	gl_mat4x4_rotate_z_axis(float _degree);

/* shear on x-direction or y-direction or z-direction */
extern t_mat4x4	gl_mat4x4_shear_x_axis(float _degree);
extern t_mat4x4	gl_mat4x4_shear_y_axis(float _degree);
extern t_mat4x4	gl_mat4x4_shear_z_axis(float _degree);

/* scale from origin (0,0,0) */
extern t_mat4x4	gl_mat4x4_scale_from_origin(float _scale_rate);
/* scale from point (x, y, z) */
extern t_mat4x4	gl_mat4x4_scale_from_point(float _x, float _y, \
											float _z, float _scale_rate);

#endif /* GL_MATRIX_H */
