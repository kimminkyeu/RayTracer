/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_viewport.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 23:30:53 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/12 22:01:02 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	render_viewport(t_device *device, t_image *viewport)
{
	/** WARN: Use Static Variable for private data member! */
	(void)device;
	// (void)viewport;

		gl_draw_background(viewport, 0x11044101);
		gl_image_brightness(viewport, 10.0f);
	return (0);
}