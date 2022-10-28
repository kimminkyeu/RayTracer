/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_engine.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:48:11 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/28 19:22:10 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_ENGINE_H
# define GL_ENGINE_H

# include <stdlib.h>					/* for Exit */
# include <stdio.h>						/* for Perror */
# include <stdbool.h>					/* for isError flag */

# define __LINUX__	(0)
# define __OSX__	(1)

# if defined (__linux__)
#  define PLATFORM_NAME (__LINUX__)
#  include "mlx_linux.h"
#  include "mlx_keymap_linux.h"
# elif defined (__APPLE__)
#  define PLATFORM_NAME (__OSX__)
#  include "mlx_macos.h"
#  include "mlx_keymap_macos.h"
# endif

/* Engine Header */
# include "libft.h"
# include "gl_device.h"
# include "gl_input.h"
# include "gl_time.h"
# include "gl_color.h"
# include "gl_matrix.h"
# include "gl_vec2.h"
# include "gl_vec3.h"
# include "gl_vec4.h"
# include "gl_draw.h"

# define STDOUT				(1)
# define ERROR				(1)
# define SUCCESS			(0)

/** #src/engine_core/engine.c.
 * Create and return Engine-instance.
 * @ title : Title of X11, window which will be displayed at top-bar.*/
extern t_device	*engine_init(char *title, char *rt_file);

/** #src/engine_core/engine.c.
 * Close Engine. (Shut down X-window)
 * NOTE: function deletes every allocated memory inside Engine-instance.
 * (Memory-leak-Safe)
 * if [is_error] is true, then exit_code will be 1 (FAIL).
 * else if [is_error] is false, then exit_code will be 0 (SUCCESS). */
extern void		engine_exit(t_device *device, bool is_error);

/** #src/engine_core/engine.c.
 * Creates new image.
 * @ img_size : width and height of the image.
 * @ img_location : x and y coordinate of where the image will be located
 * (image's top left corner).
 * NOTE: if *update_func is NULL, then nothing gets updated. */
extern t_image	*engine_new_image(t_device *device, t_vec2 img_size, \
									t_vec2 img_location);

/** #src/engine_core/engine.c.
 * Load and convert xpm-format file to t_image.
 * Returns (-1) on file-open error. / return (0) on Success.
 * NOTE: function adds image instance to t_vector images (= array of images).
 * @ img_size : width and height of the image.
 * @ img_location : x and y coordinate of where the image will be located
 * (image's top left corner).
 * NOTE: if *update_func is NULL, then nothing gets updated. */
extern t_image	*engine_new_xpm_image(t_device *device, char *filename, \
										t_vec2 img_location);

/** #src/engine_core/engine.c>
 *
 * engine_update_images() 함수 내부에서 사용됨.
 * 인자로 넘긴 이미지를 스크린 (x, y) 지점에 그린다.*/
extern void		engine_push_image_to_window(t_device *device, t_image *image, \
											int x, int y);

#endif /* ENGINE_H */
