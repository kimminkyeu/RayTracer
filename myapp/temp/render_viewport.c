/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_viewport.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 23:30:53 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/06 20:23:24 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/** NOTE: Main Shader function */
int	per_pixel(t_vec2 coord)
{
	char r = coord.x * 255.0f;
	char g = coord.y * 255.0f;

	
	// (1) Change 
	/** t_vec4 ray_direction = gl_vec4(coord.x, coord.y, -1.0f, 1.0f); */
	// Sphere Formula
	// (bx^2 + by^2)t^2 + (2(axbx + ayby))t + (ax^2 + ay^2 - r^2) = 0
	// where
	// a = ray origin
	// b = ray direction
	// r = radius
	// t = hit distance
	
	/** float a = gl_vec4_get_magnitude(ray_direction); */


	return (gl_color(BLACK, r, g, 0));
}

int	render_viewport(t_device *device, t_image *viewport)
{		
	/** WARN: Use Static Variable for private data member! */
	(void)device;

	int	x;
	int	y;
	t_vec2	coord;

	/** (1) Basic While-loop for Ray */
	y = 0;
	while (y < viewport->height)
	{
		x = 0;
		while (x < viewport->width)
		{
			// coord from (0.0f ~ 1.0f)
			coord = gl_vec2((float)x / (float)viewport->width, (float)y / (float)viewport->height);

			// Change coord value to (-1.0f ~ 1.0f)
			coord.x = coord.x * 2.0f - 1.0f;
			coord.y = coord.y * 2.0f - 1.0f;

			gl_draw_pixel(viewport, x, y, per_pixel(coord));
			x++;
		}
		y++;
	}
	return (0);
}
