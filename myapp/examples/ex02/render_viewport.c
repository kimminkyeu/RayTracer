/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_viewport.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 23:30:53 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/05 17:34:47 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

/** NOTE: Main Shader function */
int	per_pixel(t_vec2 coord)
{
	char r = coord.x * 255.0f;
	char g = coord.y * 255.0f;

	/** FIX: change gl_color functions... t_color is to bad... don't use it. */
	return (gl_color(BLACK, r, g, 0));
}

int	render_viewport(t_device *device, t_image *viewport)
{		
	/** WARN: Use Static Variable for private data member! */

	(void)device;
	/** gl_draw_background(viewport, BLACK); */

	int	x;
	int	y;

	/** (1) Basic While-loop for Ray */
	y = 0;
	while (y < viewport->height)
	{
		x = 0;
		while (x < viewport->width)
		{
			t_vec2	coord = gl_vec2((float)x / (float)viewport->width, (float)y / (float)viewport->height);
			gl_draw_pixel(viewport, x, y, per_pixel(coord));

			x++;
		}
		y++;
	}
	return (0);
}
