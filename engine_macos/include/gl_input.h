/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_input.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:44:40 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/05 23:31:48 by sungjpar         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <stdbool.h>
# include <stddef.h>
#  include "gl_keymap.h"


# include "gl_device.h"

extern t_vec2	input_get_mouse_pos(const t_device *device);
extern int		input_mouse_get_index(int key_code);
extern int		input_key_get_index(int key_code);
extern int		input_is_key_down(t_device *device, int key_code);
extern int		input_is_key_unpressed(t_device *device, int key_code);
extern int		input_is_mouse_down(t_device *device, int key_code);
extern int		input_is_mouse_unpressed(t_device *device, int key_code);


extern void		input_init(t_input *input);
extern void		input_update_mouse_pos(t_device *device, int x, int y);
extern int		handle_mouse_press(int key_code, int x, int y, void *param);
extern int		handle_mouse_release(int key_code, int x, int y, void *param);
extern int		handle_key_press(int key_code, void *param);
extern int		handle_key_release(int key_code, void *param);

#endif /* INPUT_H */
