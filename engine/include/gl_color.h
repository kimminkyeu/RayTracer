/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_color.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:54:46 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/14 16:45:10 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_COLOR_H
# define GL_COLOR_H

# include "gl_vec4.h"

# define BLACK				(0x00111111)
# define WHITE				(0x00ffffff)
# define RED				(0x00ee3333)
# define ORANGE				(0x00ff9900)
# define YELLOW				(0x00ffee00)
# define LIME				(0x00aacc11)
# define GREEN				(0x0044aa77)
# define CYAN				(0x000099ee)
# define BLUE				(0x000066bb)
# define VIOLET	  			(0x00443388)
# define PURPLE				(0x00992288)
# define MAGENTA			(0x00ee0077)
# define GRAY				(0x00949494)

/*
 * ---------------------------------
 * | a : alpha(transparency).      |
 * | r : red.                      |
 * | g : green.                    |
 * | b : blue.                     |
 * ------------------------------- */

/* (1) Create and Return integer r-value (int argb) color from each value */
extern int				gl_get_color_from_4int(int alpha, int r, int g, int b);

/* (2) Create and Return integer r-value (int argb) color from t_vec4 type*/
extern int				gl_get_color_from_vec4(t_vec4 color);

/* NOTE: [t_vec4 type] Change color brightness and return it's value.	
	* function automaticaly clamps color range from (0.0f to 255.0f).
	Example Usage = {
		t_vec4 color = gl_vec4(0, 10, 30, 0);
		color = gl_color_set_brightness(color, 10.0f);
		gl_draw_background(viewport, gl_color_(color));
	} */
extern t_vec4			gl_color_set_brightness(t_vec4 _color, double brightness_factor);

/* Return Opposite color */
extern int				gl_color_reverse(int argb);
/* Return alpha */
extern unsigned char	gl_color_get_alpha(int argb);
/* Return red */
extern unsigned char	gl_color_get_red(int argb);
/* Return green */
extern unsigned char	gl_color_get_green(int argb);
/* Return blue */
extern unsigned char	gl_color_get_blue(int argb);

#endif /* COLOR_H */
