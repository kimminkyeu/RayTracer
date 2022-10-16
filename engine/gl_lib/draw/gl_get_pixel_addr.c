/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_get_pixel_addr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 19:29:30 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/16 20:40:53 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_draw.h"

int	*gl_get_pixel_addr(t_image *_image, int _x, int _y)
{
	char	*pixel;

	pixel = _image->addr + (_y * _image->line_length) + (_x * (_image->bits_per_pixel / 8));
	return ((int *)pixel);
}
