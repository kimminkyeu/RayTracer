/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_4x4_multiply.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksungjun <parksungjun@student.42seou    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:40:02 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/05 23:18:39 by parksungjun      ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "gl_matrix.h"

t_mat4x4	gl_mat4x4_multiply(t_mat4x4 m1, t_mat4x4 m2)
{
	t_mat4x4	mat;
	int			i;
	int			j;
	int			k;

	i = -1;
	while (++i < 16)
		*(*(mat.m) + i) = 0;
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			k = -1;
			while (++k < 4)
				mat.m[i][j] += m1.m[i][k] * m2.m[k][j];
		}
	}
	return (mat);
}

/** t_mat4x4	set_z_unit(float _z_unit) */
/** { */
/**     static t_mat4x4	mat; */
/**  */
/**     mat.m[0][0] = 1.0f; */
/**     mat.m[1][1] = 1.0f; */
/**     mat.m[2][2] = _z_unit; */
/**     mat.m[3][3] = 1.0f; */
/**     return (mat); */
/** } */


/** t_mat4x4	fit_to_viewport(t_mlx *fdf) */
/** { */
/**     static t_mat4x4	mat; */
/**     float			offset_x; */
/**     float			offset_y; */
/**  */
/**     offset_x = (WIN_WIDTH - fdf->map_info.max_x) / 2; */
/**     offset_y = (WIN_HEIGHT - fdf->map_info.max_y) / 2; */
/**     mat = translate_3d(offset_x, offset_y, 0); */
/**     return (mat); */
/** } */
