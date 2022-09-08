/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_color_get_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:52:02 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/08 18:23:44 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_color.h"

/* TODO : 
 * ======================================
 * ints are stored from right to left!! |
 * ====================================== */
unsigned char	gl_color_get_alpha(int argb)
{
	return (((unsigned char *)&argb)[3]);
}

unsigned char	gl_color_get_red(int argb)
{
	return (((unsigned char *)&argb)[2]);
}

unsigned char	gl_color_get_green(int argb)
{
	return (((unsigned char *)&argb)[1]);
}

unsigned char	gl_color_get_blue(int argb)
{
	return (((unsigned char *)&argb)[0]);
}
