/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brightness.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 21:24:15 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/14 16:46:31 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_color.h"
#include "gl_shader.h"
#include "gl_vec4.h"

/** Addjust Brightness (no change in alpha) */
void	gl_image_brightness(t_image *image, float brightness_factor)
{
	int		i;
	int		j;
	int		*pixel_ptr;
	t_vec4	color;

	j = 0;
	while (j < image->img_size.height)
	{
		i = 0;
		while (i < image->img_size.width)
		{
			pixel_ptr = gl_get_pixel_addr(image, i, j);
			color.a = gl_color_get_alpha(*pixel_ptr); // keep alpha
			color.r = gl_color_get_red(*pixel_ptr) * brightness_factor;
			color.g = gl_color_get_green(*pixel_ptr) * brightness_factor;
			color.b = gl_color_get_blue(*pixel_ptr) * brightness_factor;
			color = gl_vec4_clamp(color, gl_get_vec4_from_1f(0.0f), gl_get_vec4_from_1f(255.0f));
			gl_draw_pixel(image, i, j, gl_get_color_from_4int(color.a, color.r, color.g, color.b));
			i++;
		}
		j++;
	}
}