/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:54:43 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/24 09:05:59 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/main.h"
#include "helper.h"
#include "libft.h"
#include "thread.h"

int input_handler(t_device *device)
{
	// *  NOTE:  https://www.youtube.com/watch?v=lXlXqUEEJ94
	// * Adding an Interactive 3D Camera System // Ray Tracing series


	// t_device *device = param;
	t_camera *camera = device->camera;

	// t_vec2 mouse_pos = input_get_mouse_pos(device);
	// t_vec2 delta = gl_vec2_multiply_scalar((gl_vec2_subtract_vector(mouse_pos, device->input.last_mouse_pos)), 0.002f);
	// device->input.last_mouse_pos = mouse_pos;

	// if (input_is_key_down(device, KEY_R))
	// {
		// printf("r pressed\n");
	// }
	if (!(input_is_mouse_down(device, MOUSE_RIGHT_CLICK)))
	{
		return (0);
	}
	// below code will be executed only if mouse is pressed

	bool moved = false;

	t_vec3 right_direction = gl_vec3_cross(camera->dir, gl_vec3_3f(0.0f, 1.0f, 0.0f));
	t_vec3 up_direction = gl_vec3_3f(0.0f, 1.0f, 0.0f);

	float speed = 0.1f;

	// Movement
	if (input_is_key_down(device, KEY_W))
	{
		camera->pos = gl_vec3_add_vector(camera->pos, gl_vec3_multiply_scalar(camera->dir, speed));
		moved = true;
	}
	else if (input_is_key_down(device, KEY_S))
	{
		camera->pos = gl_vec3_subtract_vector(camera->pos, gl_vec3_multiply_scalar(camera->dir, speed));
		moved = true;
	}
	if (input_is_key_down(device, KEY_A))
	{
		camera->pos = gl_vec3_subtract_vector(camera->pos, gl_vec3_multiply_scalar(right_direction, speed));
		moved = true;
	}
	else if (input_is_key_down(device, KEY_D))
	{
		camera->pos = gl_vec3_add_vector(camera->pos, gl_vec3_multiply_scalar(right_direction, speed));
		moved = true;
	}
	if (input_is_key_down(device, KEY_Q))
	{
		camera->pos = gl_vec3_subtract_vector(camera->pos, gl_vec3_multiply_scalar(up_direction, speed));
		moved = true;
	}
	else if (input_is_key_down(device, KEY_E))
	{
		camera->pos = gl_vec3_add_vector(camera->pos, gl_vec3_multiply_scalar(up_direction, speed));
		moved = true;
	}


	// (void)delta;
	if(moved)
	{
		update(device);
	}
	return (0);
}




int	main(int ac, char **av)
{
	t_device	*device;

	if (ac != 2)
	{
		//... err message
		return (EXIT_FAILURE);
	}
	const int WIDTH = 800;
	const int HEIGHT = 800;


	/** (1) Init engine && create image */
	device = engine_init(WIDTH, HEIGHT, "42 Mini-RayTracing", 8);
	// device = engine_init(WIDTH, HEIGHT, "42 Mini-RayTracing", 1);

	/** (2) Load files. (Map data etc...) then store data to [t_device] structure */
	parse_rt_file_to_device(device, av[1]);

	// TODO:  Delete later. just for parse check.
	// print_rt_data(device);

	// THREAD TEST
	t_thread_info *info = &device->thread_info;
	const int THREAD_NUM = 24;
	info->thread_group = ft_calloc(1, sizeof(t_thread) * THREAD_NUM);
	info->thread_num = THREAD_NUM;
	info->finished_thread_num = 0;
	if (pthread_mutex_init(&(info->finished_num_mutex), NULL) != 0)
		print_error_and_exit(device, "error in pthread_mutex_init()\n");


	/** (3) start rendering */


	// update on pixel_image;
	update(device);

	/** (4) loop mlx */
	mlx_loop_hook(device->mlx, input_handler, device);


	mlx_loop(device->mlx);
	return (0);
}
