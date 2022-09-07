/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_color.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:54:46 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/06 16:45:42 by sungjpar         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_COLOR_H
# define GL_COLOR_H

/* NOTE: BASIC COLOR-PALLETE */
# define BLACK				(0x00111111)
# define WHITE				(0x00ffffff)
# define RED				(0x00ee3333)
# define ORANGE				(0x00ff9900)
# define YELLOW				(0x00ffee00)
# define LIME				(0x00aacc11)
# define GREEN				(0x0044aa77)
# define CYAN				(0x000099ee)
# define BLUE				(0x000066bb)
# define VIOLETT			(0x00443388)
# define PURPLE				(0x00992288)
# define MAGENTA			(0x00ee0077)
# define GRAY				(0x00949494)

/* NOTE: typedef for ARGB color system
 * ---------------------------------
 * | t : alpha(transparency).      |
 * | r : red.                      |
 * | g : green.                    |
 * | b : blue.                     |
 * ------------------------------- */

// typedef union u_color {
//     struct {
//         char a;
//         char r;
//         char g;
//         char b;
//     };
//     int		argb;
//     char	data[4];
// } t_color;

/* Create and Return r-value (int argb) color */
extern int				gl_color(int alpha, int r, int g, int b);

/* Return alpha */
extern unsigned char	gl_color_get_alpha(int trgb);

/* Return red */
extern unsigned char	gl_color_get_red(int trgb);

/* Return green */
extern unsigned char	gl_color_get_green(int trgb);

/* Return blue */
extern unsigned char	gl_color_get_blue(int trgb);

/* Return Shaded color */
extern int				gl_color_shade(double shade_factor, int color);

/* Return Opposite color */
extern int				gl_color_reverse(int trgb);

// extern t_color			gl_create_color_char(char _alpha, char _red, char _green, char _blue);
// extern t_color			gl_create_color_int(int _argb);
/** Shading : RGB decreases, black if 0.
 * Gets Darker if shade_factor increases. */
// extern t_color			gl_shade_color(double _shade_factor, t_color _color);
/** Inverts alpha and color, and return */
// extern t_color			gl_reverse_color(t_color _color);

/* ---------------------------------------------------------------------------------- */
#endif /* COLOR_H */
