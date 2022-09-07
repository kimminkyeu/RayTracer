/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_draw_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:41:10 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/06 17:13:47 by sungjpar         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "gl_draw.h"

bool	is_inside_image(t_image *image, int _x, int _y)
{
	if (_x < image->width && _x > 0 && \
			_y < image->height && _y > 0)
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
		pixel = _image->addr + (_y * _image->line_length \
				+ _x * (_image->bits_per_pixel / 8));
		*(unsigned int *)pixel = _argb;
	}
}
