/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksungjun <parksungjun@student.42seou    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:57:40 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/06 01:07:37 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_DRAW_H
# define GL_DRAW_H

/* NOTE: deleted #ifndef macro, because of -I include option */
# include "mlx.h"
# include "gl_device.h"

/* Default Coordinate system: from (Screen Width ~ Screen Height). */
extern void	gl_draw_pixel(t_image *image, int _x, int _y, int _argb);

/* Fill every pixel of the image with (int _argb) color. */
extern void	gl_draw_background(t_image *image, int _argb);

/* Add description */
extern void	gl_draw_line(t_image *image, t_vec2 _v1, t_vec2 _v2, int _argb);

#endif /* GL_DRAW_H */
