/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:13:57 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/28 21:00:31 by minkyeki         ###   ########.fr       */
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

extern bool	is_moved(t_device *device, t_camera *const camera, \
						const t_vec2 delta);

//  NOTE:  https://www.youtube.com/watch?v=lXlXqUEEJ94
// Adding an Interactive 3D Camera System // Ray Tracing series
int	input_handler(t_device *device)
{
	t_camera *const	camera = device->camera;
	const t_vec2	mouse_pos = input_get_mouse_pos(device);
	const t_vec2	delta = gl_vec2_multiply_scalar((\
	gl_vec2_subtract_vector(mouse_pos, device->input.last_mouse_pos)), 0.1f);

	device->input.last_mouse_pos = mouse_pos;
	if (device->is_high_resolution_render_mode == false \
									&& input_is_key_down(device, KEY_R))
	{
		device->is_high_resolution_render_mode = true;
		update(device);
		return (0);
	}
	if (!(input_is_mouse_down(device, MOUSE_RIGHT_CLICK)))
		return (0);
	if (is_moved(device, camera, delta))
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
	info->thread_group = ft_calloc(1, sizeof(t_thread) \
						* device->renderer_settings.num_of_threads);
	info->thread_num = device->renderer_settings.num_of_threads;
	info->finished_thread_num = 0;
	if (pthread_mutex_init(&(info->finished_num_mutex), NULL) != 0)
		print_error_and_exit(device, "error in pthread_mutex_init()\n");
	update(device);
	mlx_loop_hook(device->mlx, input_handler, device);
	mlx_loop(device->mlx);
	return (0);
}
