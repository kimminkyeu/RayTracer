/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gaussian_blur.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 21:04:28 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/13 18:14:50 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_shader.h"

void	gl_image_gaussian_blur(t_image *img)
{
	int	i;
	int j;

	t_vec4	neighbor_color_sum;

	neighbor_color_sum = gl_vec4(0.0f, 0.0f, 0.0f, 1.0f);

	while (j < img->img_size.height)
	{
		while (i < img->img_size.width)
		{
			t_vec4 neighbor_color

			i++;
		}
	}
}
