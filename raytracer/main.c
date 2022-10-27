/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:13:57 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/27 20:20:05 by minkyeki         ###   ########.fr       */
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

// *  NOTE:  https://www.youtube.com/watch?v=lXlXqUEEJ94
// * Adding an Interactive 3D Camera System // Ray Tracing series
int	input_handler(t_device *device)
{
	t_camera *const	camera = device->camera;
	const float		speed = 0.2f;
	const t_vec2	mouse_pos = input_get_mouse_pos(device);
	const t_vec2	delta = gl_vec2_multiply_scalar((\
	gl_vec2_subtract_vector(mouse_pos, device->input.last_mouse_pos)), 0.1f);

	device->input.last_mouse_pos = mouse_pos;
	if (device->is_high_resolution_render_mode == false && input_is_key_down(device, KEY_R))
	{
		printf("[change to High Resolution mode]\n");
		device->is_high_resolution_render_mode = true;
		update(device);
		return (0);
	}
	if (!(input_is_mouse_down(device, MOUSE_RIGHT_CLICK)))
		return (0);
	bool moved = false;
	if (input_is_key_down(device, KEY_W))
	{
		camera->pos = gl_vec3_add_vector(camera->pos, gl_vec3_multiply_scalar(camera->look_at, speed));
		moved = true;
	}
	else if (input_is_key_down(device, KEY_S))
	{
		camera->pos = gl_vec3_subtract_vector(camera->pos, gl_vec3_multiply_scalar(camera->look_at, speed));
		moved = true;
	}
	if (input_is_key_down(device, KEY_A))
	{
		camera->pos = gl_vec3_subtract_vector(camera->pos, gl_vec3_multiply_scalar(camera->right_direction, speed));
		moved = true;
	}
	else if (input_is_key_down(device, KEY_D))
	{
		camera->pos = gl_vec3_add_vector(camera->pos, gl_vec3_multiply_scalar(camera->right_direction, speed));
		moved = true;
	}
	if (input_is_key_down(device, KEY_Q))
	{
		camera->pos = gl_vec3_subtract_vector(camera->pos, gl_vec3_multiply_scalar(camera->up_direction, speed));
		moved = true;
	}
	else if (input_is_key_down(device, KEY_E))
	{
		camera->pos = gl_vec3_add_vector(camera->pos, gl_vec3_multiply_scalar(camera->up_direction, speed));
		moved = true;
	}
	if (delta.x != 0.0f || delta.y != 0.0f)
	{
		t_vec4 cam_look_at = gl_vec4_4f(camera->look_at.x, camera->look_at.y, camera->look_at.z, 0.0f);
		cam_look_at.x = gl_vec4_multiply_matrix(gl_mat4x4_rotate_y_axis(delta.x),cam_look_at).x;
		cam_look_at.y = gl_vec4_multiply_matrix(gl_mat4x4_rotate_x_axis(-delta.y), cam_look_at).y;
		camera->look_at = gl_vec3_3f(cam_look_at.x, cam_look_at.y, cam_look_at.z);
		t_vec4 cam_up = gl_vec4_4f(camera->up_direction.x, camera->up_direction.y, camera->up_direction.z, 0.0f);
		cam_up.x = gl_vec4_multiply_matrix(gl_mat4x4_rotate_y_axis(delta.x),cam_up).x;
		cam_up.y = gl_vec4_multiply_matrix(gl_mat4x4_rotate_x_axis(-delta.y),cam_up).y;
		camera->up_direction = gl_vec3_3f(cam_up.x, cam_up.y, cam_up.z);
		moved = true;
	}
	if(moved)
	{
		device->is_high_resolution_render_mode = false;
		update_camera_geometry(device);
		update(device);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_device		*device;
	t_thread_info	*info;

	if (ac != 2)
	{
		printf("Please enter .rt file\n");
		return (EXIT_FAILURE);
	}
	device = engine_init("42 Mini-RayTracing", av[1]);
	info = &device->thread_info;
	info->thread_group = ft_calloc(1, sizeof(t_thread) * device->renderer_settings.num_of_threads);
	info->thread_num = device->renderer_settings.num_of_threads;
	info->finished_thread_num = 0;
	if (pthread_mutex_init(&(info->finished_num_mutex), NULL) != 0)
		print_error_and_exit(device, "error in pthread_mutex_init()\n");
	update(device);
	mlx_loop_hook(device->mlx, input_handler, device);
	mlx_loop(device->mlx);
	return (0);
}
