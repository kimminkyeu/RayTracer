/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 20:56:30 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/28 20:56:33 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "camera.h"
#include "include/main.h"
#include "gl_vec3.h"
#include "helper.h"
#include "libft.h"
#include "thread.h"
#include "parser.h"

#define SPEED (0.2f)

bool	is_key_pressed_1(t_device *device, t_camera *const camera)
{
	if (input_is_key_down(device, KEY_W))
	{
		camera->pos = gl_vec3_add_vector(camera->pos, \
			gl_vec3_multiply_scalar(camera->look_at, SPEED));
		return (true);
	}
	else if (input_is_key_down(device, KEY_S))
	{
		camera->pos = gl_vec3_subtract_vector(camera->pos, \
			gl_vec3_multiply_scalar(camera->look_at, SPEED));
		return (true);
	}
	else if (input_is_key_down(device, KEY_A))
	{
		camera->pos = gl_vec3_subtract_vector(camera->pos, \
			gl_vec3_multiply_scalar(camera->right_direction, SPEED));
		return (true);
	}
	else if (input_is_key_down(device, KEY_D))
	{
		camera->pos = gl_vec3_add_vector(camera->pos, \
			gl_vec3_multiply_scalar(camera->right_direction, SPEED));
		return (true);
	}
	return (false);
}

bool	is_key_pressed_2(t_device *device, t_camera *const camera)
{
	if (input_is_key_down(device, KEY_Q))
	{
		camera->pos = gl_vec3_subtract_vector(camera->pos, \
			gl_vec3_multiply_scalar(camera->up_direction, SPEED));
		return (true);
	}
	else if (input_is_key_down(device, KEY_E))
	{
		camera->pos = gl_vec3_add_vector(camera->pos, \
			gl_vec3_multiply_scalar(camera->up_direction, SPEED));
		return (true);
	}
	else if (input_is_key_down(device, KEY_1) \
								&& device->point_lights->size == 1)
	{
		((t_light *)device->point_lights->data[0])->pos = camera->pos;
		return (true);
	}
	return (false);
}

bool	is_mouse_moved(t_camera *const camera, t_vec2 delta)
{
	t_vec4	cam_look_at;
	t_vec4	cam_up;

	if (delta.x != 0.0f || delta.y != 0.0f)
	{
		cam_look_at = gl_vec4_4f(camera->look_at.x, camera->look_at.y, \
									camera->look_at.z, 0.0f);
		cam_look_at.x = gl_vec4_multiply_matrix(\
					gl_mat4x4_rotate_y_axis(delta.x), cam_look_at).x;
		cam_look_at.y = gl_vec4_multiply_matrix(\
					gl_mat4x4_rotate_x_axis(-delta.y), cam_look_at).y;
		camera->look_at = gl_vec3_3f(cam_look_at.x, cam_look_at.y, \
										cam_look_at.z);
		cam_up = gl_vec4_4f(camera->up_direction.x, camera->up_direction.y, \
								camera->up_direction.z, 0.0f);
		cam_up.x = gl_vec4_multiply_matrix(gl_mat4x4_rotate_y_axis(delta.x), \
											cam_up).x;
		cam_up.y = gl_vec4_multiply_matrix(gl_mat4x4_rotate_x_axis(-delta.y), \
											cam_up).y;
		camera->up_direction = gl_vec3_3f(cam_up.x, cam_up.y, cam_up.z);
		return (true);
	}
	return (false);
}

bool	is_moved(t_device *device, t_camera *const camera, const t_vec2 delta)
{
	if (is_key_pressed_1(device, camera) || is_key_pressed_2(device, camera))
		return (true);
	if (is_mouse_moved(camera, delta))
		return (true);
	return (false);
}
