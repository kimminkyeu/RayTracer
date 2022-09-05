/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_color_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksungjun <parksungjun@student.42seou    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 19:03:43 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/05 23:14:44 by parksungjun      ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "gl_color.h"

int	gl_color(int alpha, int r, int g, int b)
{
	unsigned char	color[4];

	color[0] = b;
	color[1] = g;
	color[2] = r;
	color[3] = alpha;
	return (*(int *)(color));
}

/* get_shaded_color is a function that accepts a double (distance) 
 * and a int (color) as arguments, 0 will add no shading to the color, 
 * whilst 1 will make the color completely dark. 
 * 0.5 will dim it halfway, and .25 a quarter way.  */
/* ------------------------------
 * * Shading : RGB decreases, black if 0.
 * Gets Darker if shade_factor increases. */
int	gl_color_shade(double shade_factor, int color)
{
	unsigned char	shaded_red;
	unsigned char	shaded_green;
	unsigned char	shaded_blue;
	unsigned char	alpha;

	if (shade_factor <= 0)
		return (color);
	shaded_red = gl_color_get_red(color) * (1 - shade_factor);
	shaded_green = gl_color_get_green(color) * (1 - shade_factor);
	shaded_blue = gl_color_get_blue(color) * (1 - shade_factor);
	alpha = gl_color_get_alpha(color);
	return (gl_color(alpha, shaded_red, shaded_green, shaded_blue));
}

/* NOTE : Inverts alpha and color, and return */
int	gl_color_reverse(int trgb)
{
	unsigned char	oppo[4];

	oppo[3] = 0xFF - gl_color_get_alpha(trgb);
	oppo[2] = 0xFF - gl_color_get_red(trgb);
	oppo[1] = 0xFF - gl_color_get_green(trgb);
	oppo[0] = 0xFF - gl_color_get_blue(trgb);
	return (*(int *)oppo);
}
