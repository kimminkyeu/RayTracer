/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_color_get_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:52:02 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 11:58:57 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_color.h"
#include "gl_vec4.h"

/* NOTE:  ints are stored from right to left!! */

int	gl_get_color_from_4int(int alpha, int r, int g, int b)
{
	unsigned char	color[4];

	color[0] = b;
	color[1] = g;
	color[2] = r;
	color[3] = alpha;
	return (*(int *)(color));
}

int	gl_get_color_from_vec4(t_vec4 color)
{
	return (gl_get_color_from_4int(color.a, color.r, color.g, color.b));
}

t_vec4	gl_get_vec4_from_color(int argb)
{
	t_vec4	color;

	color.a = gl_color_get_alpha(argb);
	color.r = gl_color_get_red(argb);
	color.g = gl_color_get_green(argb);
	color.b = gl_color_get_blue(argb);
	return (color);
}
