/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_engine.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:48:11 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/05 23:31:46 by sungjpar         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <stdlib.h>					/* for Exit */
# include <stdio.h>						/* for Perror */
# include <stdbool.h>					/* for isError flag */

#  include "mlx.h"
#  include "gl_keymap.h"

/* Engine Header */
# include "gl_device.h"
# include "gl_input.h"
# include "libft.h"
# include "gl_time.h"
# include "gl_color.h"
# include "gl_matrix.h"
# include "gl_vec2.h"
# include "gl_vec4.h"
# include "gl_draw.h"

# define STDOUT				(1)
# define ERROR				(1)
# define SUCCESS			(0)

/* #src/engine_core/engine.c */
extern t_device	*engine_init(int _viewport_width, int _panel_width, int _win_height, char *title);

/* #src/engine_core/engine.c */
extern void		engine_exit(t_device *device, bool is_error);

/* #src/engine_core/engine.c */
extern void		engine_start_loop(t_device *device, int (*render_layer)());

/* #src/engine_core/engine.c */
extern void		engine_set_key_event(t_device *device, int (*f_key_press)(), int (*f_key_release)());

/* #src/engine_core/engine.c */
extern void		engine_set_mouse_event(t_device *device, int (*f_mouse_press)(), int (*f_mouse_release)());

    /* #src/engine_core/engine.c */
extern void		engine_push_image(t_device *device, t_image *image, int x, int y);

#endif /* ENGINE_H */
