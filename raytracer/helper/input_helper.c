/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 20:56:30 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/30 23:01:40 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "camera.h"
#include "gl_device.h"
#include "gl_matrix.h"
#include "gl_vec2.h"
#include "gl_vec4.h"
#include "main.h"
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
		camera->pos = add3(camera->pos, \
            mult3_scalar(camera->look_at, SPEED));
		return (true);
	}
	else if (input_is_key_down(device, KEY_S))
	{
		camera->pos = sub3(camera->pos, \
            mult3_scalar(camera->look_at, SPEED));
		return (true);
	}
	else if (input_is_key_down(device, KEY_A))
	{
		camera->pos = sub3(camera->pos, \
            mult3_scalar(camera->right_direction, SPEED));
		return (true);
	}
	else if (input_is_key_down(device, KEY_D))
	{
		camera->pos = add3(camera->pos, \
            mult3_scalar(camera->right_direction, SPEED));
		return (true);
	}
	return (false);
}

bool	is_key_pressed_2(t_device *device, t_camera *const camera)
{
	if (input_is_key_down(device, KEY_Q))
	{
		camera->pos = sub3(camera->pos, \
            mult3_scalar(camera->up_direction, SPEED));
		return (true);
	}
	else if (input_is_key_down(device, KEY_E))
	{
		camera->pos = add3(camera->pos, \
            mult3_scalar(camera->up_direction, SPEED));
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

/** *  NOTE:  (!) How to Solve Gymbol-lock
 * 	[ From 3D Rotation About Arbitrary Axis ]
 * 	1. restore angle to 0. ( Use camera's rotated angle)
 *  2. rotate via y axis
 * 	3. restor angle from 0 to previous angle.
 */
t_mat4x4	get_rotation_matrix(t_camera *const camera, t_vec2 delta)
{
	const t_mat4x4	y_axis_rotation = gl_mat4x4_rotate_y_axis(delta.x);
	const t_mat4x4	x_axis_rotation = gl_mat4x4_rotate_x_axis(-delta.y);
	t_mat4x4		to_origin;
	t_mat4x4		to_origin_reverse;
	t_mat4x4		rotation_matrix;

	to_origin = gl_mat4x4_rotate_y_axis(-(camera->rotation_delta.x));
	to_origin_reverse = gl_mat4x4_rotate_y_axis(camera->rotation_delta.x);
	rotation_matrix = gl_mat4x4_multiply(y_axis_rotation, x_axis_rotation);
	rotation_matrix = gl_mat4x4_multiply(rotation_matrix, to_origin);
	rotation_matrix = gl_mat4x4_multiply(to_origin_reverse, rotation_matrix);
	return (rotation_matrix);
}

bool	is_mouse_moved(t_camera *const camera, t_vec2 delta)
{
	t_vec4		cam_look_at;
	t_vec4		cam_up;
	t_mat4x4	rotation_matrix;

	if (delta.x != 0.0f || delta.y != 0.0f)
	{
		rotation_matrix = get_rotation_matrix(camera, delta);
		cam_look_at = vec4_4f(camera->look_at.x, camera->look_at.y, \
                                    camera->look_at.z, 0.0f);
		cam_look_at = gl_vec4_multiply_matrix(rotation_matrix, cam_look_at);
		camera->look_at = vec3_3f(cam_look_at.x, cam_look_at.y, \
                                        cam_look_at.z);
		cam_up = vec4_4f(camera->up_direction.x, camera->up_direction.y, \
                                camera->up_direction.z, 0.0f);
		cam_up = gl_vec4_multiply_matrix(rotation_matrix, cam_up);
		camera->up_direction = vec3_3f(cam_up.x, cam_up.y, cam_up.z);
		camera->rotation_delta.x += delta.x;
		camera->rotation_delta.y -= delta.y;
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
