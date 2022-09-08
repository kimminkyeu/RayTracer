/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_input.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:44:40 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/08 16:25:31 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_INPUT_H
# define GL_INPUT_H

# include <stdbool.h>
# include <stddef.h>
# if defined (__linux__)
#  define PLATFORM_NAME (__LINUX__)
#  include "gl_keymap_linux.h"
# elif defined (__APPLE__)
#  define PLATFORM_NAME (__OSX__)
#  include "gl_keymap_macos.h"
# endif
# include "gl_device.h"

/* #engine/gl_core/input.c
 * -  NOTE: Use this function only for keyboard-input checking.
 * - Returns true (1) if key_code passed as argument is down (= pressed).
 * - Else, function returns false (0). */
extern int		input_is_key_down(t_device *device, int key_code);

/* #engine/gl_core/input.c
 * -  NOTE: Use this function only for keyboard-input checking.
 * - Returns true(1) if key_code passed as argument is up (= unpressed)
 * - Else, function returns false (0). */
extern int		input_is_key_unpressed(t_device *device, int key_code);

/* #engine/gl_core/input.c
 * -  NOTE: Use this function only for Mouse-input checking.
 * - Returns true(1) if key_code passed as argument is down (=pressed)
 * - Else, function returns false (0)*/
extern int		input_is_mouse_down(t_device *device, int key_code);

/* #engine/gl_core/input.c
 * -  NOTE: Use this function only for Mouse-input checking.
 * - Returns true(1) if key_code passed as argument is up (= unpressed)
 * - Else, function returns false (0)*/
extern int		input_is_mouse_unpressed(t_device *device, int key_code);

/* #engine/gl_core/input.c
 * - Get mouse position and return as t_vec2 type data. (x, y) */
extern t_vec2	input_get_mouse_pos(const t_device *device);

/* #engine/gl_core/input.c
 * - Default input-detector initializer.
 * - Ex) t_input _input --> input_init(&_input) */
// FIXME: 사용 안하는 코드
// extern void		input_init(t_input *input);


/* extern int		input_mouse_get_index(int key_code);
 * extern int		input_key_get_index(int key_code);
 * extern void		input_update_mouse_pos(t_device *device, int x, int y);
 * extern int		handle_mouse_press(int key_code, int x, int y, void *param);
 * extern int		handle_mouse_release(int key_code, int x, int y, void *param);
 * extern int		handle_key_press(int key_code, void *param);
 * extern int		handle_key_release(int key_code, void *param); */

#endif /* INPUT_H */
