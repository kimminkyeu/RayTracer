/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_draw_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:41:10 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/04 21:43:39 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_draw.h"

void	gl_draw_pixel(t_image *image, int _x, int _y, int argb)
{
	char	*pixel;

	if (_x < image->width && _x > 0 && \
			_y < image->height && _y > 0)
	{
		pixel = image->addr + (_y * image->line_length \
				+ _x * (image->bits_per_pixel / 8));
		*(unsigned int *)pixel = argb;
	}
}
