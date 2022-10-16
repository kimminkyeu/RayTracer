/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_draw_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:41:10 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/16 21:00:01 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_draw.h"

static bool	is_inside_image(t_image *image, int _x, int _y)
{
	if (_x < image->img_size.width && _x >= 0 && \
			_y < image->img_size.height && _y >= 0)
	{
		return (true);
	}
	else
		return (false);
}

void	gl_draw_pixel(t_image *_image, int _x, int _y, int _argb)
{
	char	*pixel;

	if (is_inside_image(_image, _x, _y))
	{
		pixel = _image->addr + (_y * _image->line_length) + (_x * (_image->bits_per_pixel / 8));
		*(unsigned int *)pixel = _argb;
	}
}
