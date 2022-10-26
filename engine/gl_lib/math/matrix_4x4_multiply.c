/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_4x4_multiply.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:40:02 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 12:14:46 by minkyeki         ###   ########.fr       */
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
