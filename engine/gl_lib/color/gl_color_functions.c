/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_color_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 19:03:43 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 11:59:34 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_color.h"

/*
 * get_shaded_color is a function that accepts a double (distance)
 * and a int (color) as arguments, 0 will add no shading to the color,
 * whilst 1 will make the color completely dark.
 * 0.5 will dim it halfway, and .25 a quarter way.
 * * Shading : RGB decreases, black if 0.
 * Gets Darker if shade_factor increases. */
t_vec4	gl_color_set_brightness(t_vec4 _color, double brightness_factor)
{
	t_vec4	color;

	color.r = _color.r * brightness_factor;
	color.g = _color.g * brightness_factor;
	color.b = _color.b * brightness_factor;
	color.a = _color.a;
	color = clamp4(color, vec4_1f(0.0f), vec4_1f(255.0f));
	return (color);
}

/* NOTE : Inverts alpha and color, and return */
int	gl_color_reverse(int argb)
{
	unsigned char	opposite[4];

	opposite[3] = 0xFF - gl_color_get_alpha(argb);
	opposite[2] = 0xFF - gl_color_get_red(argb);
	opposite[1] = 0xFF - gl_color_get_green(argb);
	opposite[0] = 0xFF - gl_color_get_blue(argb);
	return (*(int *)opposite);
}
