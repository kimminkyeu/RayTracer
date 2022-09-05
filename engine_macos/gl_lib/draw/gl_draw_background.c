/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_draw_background.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:42:11 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/04 21:44:00 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_draw.h"

void	gl_draw_background(t_image *image, int argb)
{
	int	x;
	int	y;

	y = 0;
	while (y < (int)image->height)
	{
		x = 0;
		while (x < (int)image->width)
		{
			gl_draw_pixel(image, x, y, argb);
			x += 1;
		}
		y += 1;
	}
}
